#include <iostream>
#include <string>
#include "Markov_Chain.hpp" // Assuming this contains your MarkovChain class

enum choice
{
    GENERATE_STATE = 1,
    EXIT,
    SOLVE_STATE
};

int main()
{
    MarkovChain mc("input.txt", "output.txt");

    while (true)
    {
        // Display menu
        std::cout << "Choose your options..." << std::endl;
        std::cout << "1. Generate a random state" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "3. Solve stationary distribution" << std::endl;

        int decision;
        std::cin >> decision;

        choice userChoice = static_cast<choice>(decision);

        switch (userChoice)
        {
        case GENERATE_STATE:
        {
            // Generate a random state
            int initialState = mc.determine_state(mc.initialProbabilities);
            std::cout << "Generated state: " << mc.states[initialState] << std::endl;
            break;
        }
        case EXIT:
        {
            // Exit the program
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            return 0; // Terminate the program
        }
        case SOLVE_STATE:
        {
            // Solve for the stationary distribution
            std::vector<double> stationaryDistribution = mc.computeStationaryDistribution();
            std::cout << "Stationary Distribution:" << std::endl;
            for (size_t i = 0; i < stationaryDistribution.size(); ++i)
            {
                std::cout << mc.states[i] << ": " << stationaryDistribution[i] << std::endl;
            }
            break;
        }
        default:
        {
            // Handle invalid input
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
        }
    }

    return 0;
}