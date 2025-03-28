#include <iostream>
#include "Markov_Chain.hpp"

enum choice
{
    GENERATE_STATE = 1,
    EXIT,
    SOLVE_STATE
};

int main()
{
    MarkovChain mc("input.txt", "output.txt");
    std::cout << "Choose your options (just type the number)" << std::endl;
    std::cout << "1. Generate a random state" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << "3. Solve stationary distribution" << std::endl;

    int decision;
    std::cin >> decision;
    choice userChoice = static_cast<choice>(decision);
    switch (userChoice)
    {
    case GENERATE_STATE:
        int initialState = mc.determine_state(mc.initialProbabilities);
        std::cout << "Generated state: " << mc.states[initialState] << std::endl;
        break;
    case SOLVE_STATE:
        break;
    case EXIT:
        break;
    default:
        std::cout << "Invalid option. Please try again." << std::endl;
        break;
    }
    return 0;
}