#include <iostream>
#include <string>
#include "MarkovChain.hpp"

enum choice
{
    GENERATE_STATE = 1,
    EXIT,
    SOLVE_STATIONARY,
    SOLVE_STATIONARY_M2,
    SIMULATE,
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
        std::cout << "4. Solve stationary distribution using the power method" << std::endl;
        std::cout << "5. Simulate the Markov chain" << std::endl;
        std::cout << "Enter your choice: ";

        int decision;
        if (!(std::cin >> decision))
        {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue;
        }

        choice userChoice = static_cast<choice>(decision);

        switch (userChoice)
        {
        case GENERATE_STATE:
        {
            // Generate a random state using the initial probability distribution.
            int initialState = mc.determine_state(mc.initialProbabilities);
            std::cout << "Generated state: " << mc.states[initialState] << std::endl;
            break;
        }
        case SIMULATE:
        {
            // Simulate the Markov chain for a given number of steps.
            int numSteps;
            std::cout << "Enter the number of steps: ";
            if (!(std::cin >> numSteps))
            {
                std::cout << "Invalid input. Please enter an integer." << std::endl;
                std::cin.clear(); // clear the error flag on the std::cin stream, allow to input again
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // the invalid input is still in the input buffer, use ignore to discard it
                continue;
            }

            std::vector<std::string>  steps = mc.simulate(numSteps,0);
            for(const std::string& step: steps){
                mc.write_file(step);
                std::cout << step << std::endl;
            }
            mc.write_file("\n================================");
            break;
        }
        case EXIT:
        {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            return 0;
        }
        case SOLVE_STATIONARY:
        {
            // Solve for the stationary distribution.
            Eigen::VectorXd stationaryDistribution = mc.computeStationaryDistribution();
            std::cout << "Stationary Distribution:" << std::endl;
            for (int i = 0; i < stationaryDistribution.size(); ++i)
            {
                std::cout << mc.states[i] << ": " << stationaryDistribution(i) << std::endl;
            }
            break;
        }
        case SOLVE_STATIONARY_M2:
        {
            // Solve for the stationary distribution using the power method.
            Eigen::VectorXd stationaryDistribution = mc.Power_Method();
            std::cout << "Stationary Distribution using the power method:" << std::endl;
            for (int i = 0; i < stationaryDistribution.size(); ++i)
            {
                std::cout << mc.states[i] << ": " << stationaryDistribution(i) << std::endl;
            }
            break;
        }
        default:
        {
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
        }
    }

    return 0;
}