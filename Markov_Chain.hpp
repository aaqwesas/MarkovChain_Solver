#ifndef MARKOV_CHAIN_HPP
#define MARKOV_CHAIN_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <stdexcept>
#include <eigen3/Eigen/Dense>

class MarkovChain
{
private:
    std::ifstream inputStream;
    std::ofstream outputStream;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dis;

public:
    std::vector<std::vector<double>> transitionMatrix;
    std::vector<double> initialProbabilities;
    std::vector<std::string> states;
    int numStates;

    MarkovChain(const std::string &inputFileName, const std::string &outputFileName);
    ~MarkovChain();
    double generate();
    int determine_state(const std::vector<double> &probabilities);

    std::vector<double> computeStationaryDistribution();
    void write_file(const std::string line);
    std::vector<std::string> simultae(int steps, int startState = -1);
};

#endif