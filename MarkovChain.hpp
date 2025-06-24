#ifndef MARKOVCHAIN_HPP
#define MARKOVCHAIN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <stdexcept>
#include <vector>
#include <eigen3/Eigen/Dense>

class MarkovChain
{
private:
    std::ifstream inputStream;
    std::ofstream outputStream;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dis;

public:
    // Use Eigen types for numerical data.
    Eigen::MatrixXd transitionMatrix; //!< Transition matrix as Eigen::MatrixXd.
    Eigen::VectorXd initialProbabilities; //!< Initial probabilities as Eigen::VectorXd.
    std::vector<std::string> states; //!< States remain a vector of string.
    int numStates;

    // Constructor and destructor
    MarkovChain(const std::string &inputFileName, const std::string &outputFileName);
    ~MarkovChain();

    // Helper methods
    double generate();
    int determine_state(const Eigen::VectorXd &probabilities);

    // Methods to compute stationary distributions using Eigen.
    Eigen::VectorXd computeStationaryDistribution();
    Eigen::VectorXd Power_Method(int max_iterations = 1000);

    // File output and simulation method.
    void write_file(const std::string &line);
    std::vector<std::string> simulate(int steps, int startState = -1);
};

#endif