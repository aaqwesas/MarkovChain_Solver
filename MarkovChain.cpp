#include "MarkovChain.hpp"

MarkovChain::MarkovChain(const std::string &inputFileName, const std::string &outputFileName)
    : gen(std::random_device{}()), dis(0.0, 1.0)
{
    // Open the input file
    inputStream.open(inputFileName);
    if (!inputStream.is_open())
    {
        throw std::runtime_error("Error: Could not open input file!");
    }

    // Open the output file
    outputStream.open(outputFileName, std::ios::app);
    if (!outputStream.is_open())
    {
        throw std::runtime_error("Error: Could not open output file!");
    }

    // Read the number of states.
    inputStream >> numStates;

    // Read state names.
    std::string stateName;
    for (int i = 0; i < numStates; ++i)
    {
        inputStream >> stateName;
        states.push_back(stateName);
    }

    // Allocate and read the initial probabilities.
    initialProbabilities.resize(numStates);
    for (int i = 0; i < numStates; ++i)
    {
        double probability;
        inputStream >> probability;
        initialProbabilities(i) = probability;
    }

    // Allocate and read the transition matrix.
    transitionMatrix.resize(numStates, numStates);
    for (int i = 0; i < numStates; ++i)
    {
        for (int j = 0; j < numStates; ++j)
        {
            double prob;
            inputStream >> prob;
            transitionMatrix(i, j) = prob;
        }
    }
}

double MarkovChain::generate()
{
    return dis(gen);
}

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
}

int MarkovChain::determine_state(const Eigen::VectorXd &probabilities)
{
    // Generate a random number between 0.0 and 1.0.
    double randomValue = generate();
    double cumulativeProbability = 0.0;

    // Iterate though the probabilities to select the state.
    for (int i = 0; i < probabilities.size(); ++i)
    {
        cumulativeProbability += probabilities(i);
        if (randomValue <= cumulativeProbability)
        {
            return i; // Return the selected state.
        }
    }
    return -1; // Error case (should not occur if probabilities are valid).
}

Eigen::VectorXd MarkovChain::Power_Method(int max_iterations)
{
    // Initialize x to uniform distribution.
    Eigen::VectorXd x = Eigen::VectorXd::Ones(numStates) / numStates;
    double tolerance = 1e-6;

    // Perform the power method.
    for (int i = 0; i < max_iterations; ++i)
    {
        Eigen::VectorXd y = transitionMatrix.transpose() * x;
        if ((x - y).norm() < tolerance)
        {
            return y;
        }
        x = y;
    }
    return x;
}

Eigen::VectorXd MarkovChain::computeStationaryDistribution()
{
    // Solve the system (P^T - I)x = 0 with the normalization constraint sum(x) = 1.

    // Compute the transposed transition matrix.
    Eigen::MatrixXd P_T = transitionMatrix.transpose();

    // Adjust the diagonal: P_T(i, i) becomes P_T(i, i)-1.
    for (int i = 0; i < numStates; ++i)
    {
        P_T(i, i) -= 1.0;
    }

    // Build an augmented system with an additional normalization equation.
    Eigen::MatrixXd A(numStates + 1, numStates);
    A.block(0, 0, numStates, numStates) = P_T;
    A.row(numStates) = Eigen::RowVectorXd::Ones(numStates);

    Eigen::VectorXd b = Eigen::VectorXd::Zero(numStates + 1);
    b(numStates) = 1.0; // Normalization constraint.

    // Use a least-squares solver.
    Eigen::VectorXd stationaryDistribution = A.colPivHouseholderQr().solve(b);
    return stationaryDistribution;
}

void MarkovChain::write_file(const std::string &line)
{
    if (!outputStream.is_open())
    {
        throw std::runtime_error("Error: Could not open output file!");
    }
    outputStream << line << "\n";
}

std::vector<std::string> MarkovChain::simulate(int steps, int startState)
{
    std::vector<std::string> simulationResult;
    // Determine the initial state: use startState if specified or sample according to initialProbabilities.
    int currentState = (startState >= 0) ? startState : determine_state(initialProbabilities);

    for (int i = 0; i < steps; ++i)
    {
        simulationResult.push_back(states[currentState]);
        // Get the probability vector corresponding to the current state.
        // Note: transitionMatrix.row(currentState) returns a RowVectorXd so we transpose it.
        currentState = determine_state(transitionMatrix.row(currentState).transpose());
    }
    return simulationResult;
}