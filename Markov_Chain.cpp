#include "Markov_Chain.hpp"

MarkovChain::MarkovChain(const std::string &inputFileName, const std::string &outputFileName) : gen(std::random_device{}()), dis(0.0, 1.0)
{
    this->inputStream.open(inputFileName);
    if (!inputStream.is_open())
    {
        throw std::runtime_error("Error: Could not open input file!");
    }

    // Open the output file
    this->outputStream.open(outputFileName, std::ios::app);
    if (!outputStream.is_open())
    {
        throw std::runtime_error("Error: Could not open output file!");
    }
    this->inputStream >> this->numStates;
    for (int i = 0; i < this->numStates; ++i)
    {
        std::string stateName;
        inputStream >> stateName;
        states.push_back(stateName);
    }
    for (int i = 0; i < this->numStates; ++i)
    {
        double probability;
        inputStream >> probability;
        initialProbabilities.push_back(probability);
    }
    for (int i = 0; i < this->numStates; ++i)
    {
        for (int j = 0; j < this->numStates; ++j)
        {
            inputStream >> transitionMatrix[i][j];
        }
    }
};

double MarkovChain::generate()
{
    return dis(gen);
};

MarkovChain::~MarkovChain()
{
    if (inputStream.is_open())
    {
        inputStream.close();
    }

    if (outputStream.is_open())
    {
        outputStream.close();
    }
};

int MarkovChain::determine_state(const std::vector<double> &probabilities)
{
    // Generate a random number between 0.0 and 1.0
    double randomValue = this->generate();
    double cumulativeProbability = 0.0;

    // Iterate through the probabilities to find the corresponding state
    for (int state = 0; state < probabilities.size(); ++state)
    {
        cumulativeProbability += probabilities[state];
        if (randomValue <= cumulativeProbability)
        {
            return state; // Return the selected state
        }
    }

    return -1; // Error case (shouldn't happen if probabilities are valid)
}

std::vector<double> MarkovChain::computeStationaryDistribution()
{
    Eigen::MatrixXd P(this->numStates, this->numStates);
    for (int i = 0; i < numStates; ++i)
    {
        for (int j = 0; j < numStates; ++j)
        {
            P(i, j) = transitionMatrix[i][j];
        }
    }

    // Transpose the matrix (we solve for the left eigenvector)
    Eigen::MatrixXd P_T = P.transpose();

    // Subtract the identity matrix
    for (int i = 0; i < numStates; ++i)
    {
        P_T(i, i) -= 1.0;
    }

    // Add the normalization constraint (sum of probabilities = 1)
    Eigen::MatrixXd A(numStates + 1, numStates);
    A << P_T, Eigen::VectorXd::Ones(numStates).transpose();

    Eigen::VectorXd b = Eigen::VectorXd::Zero(numStates + 1);
    b(numStates) = 1.0; // Normalization constraint

    // Solve the linear system
    Eigen::VectorXd stationaryDistribution = A.colPivHouseholderQr().solve(b);

    // Convert the Eigen vector to a std::vector
    std::vector<double> result(numStates);
    for (int i = 0; i < numStates; ++i)
    {
        result[i] = stationaryDistribution(i);
    }

    return result;
}

void MarkovChain::write_file(const std::string line)
{
    if (!outputStream.is_open())
    {
        throw std::runtime_error("Error: Could not open output file!");
    }
    this->outputStream << line << "\n";
}

std::vector<std::string> MarkovChain::simultae(int steps, int startState)
{
    std::vector<std::string> simulationResult;
    int currentState = startState >= 0 ? startState : determine_state(initialProbabilities);
    for (int i = 0; i < steps; ++i)
    {
        simulationResult.push_back(states[currentState]);
        currentState = determine_state(transitionMatrix[currentState]);
    }
    return simulationResult;
}