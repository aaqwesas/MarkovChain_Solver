# Markov Chain Solver

This project is a **Markov Chain Solver** implemented in C++. It provides tools to analyze and simulate Markov chains, including determining states, simulating transitions, and computing the stationary distribution of a Markov chain.

---

## Features

### Completed

- **Determine State**: Given a probability vector (e.g., initial probabilities or transition probabilities), it determines the next state based on random sampling.
- **Simulate Markov Chain**: Simulates the Markov chain for a specified number of steps, starting from a given state or using the initial distribution.
- **Compute Stationary Distribution**: Computes the stationary distribution of the Markov chain using the eigenvalue method, ensuring mathematically accurate results.

### Planned

- **Hitting Time Calculation**: Compute the expected number of steps to reach a specific target state from another state.
- **Absorbing States Detection**: Identify absorbing states in the Markov chain.
- **Validation**: Validate the transition matrix (e.g., ensure rows sum to $1$).
- **Matrix Operations**: Add support for raising the transition matrix to a power ($P^n$).
- **File I/O Enhancements**: Save simulation results to a file for further analysis.
- **Visualization**: Add methods to print or visualize the transition matrix and simulation results.
- TBC

---

## Installation

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler that supports the C++11 standard or later.
- **Eigen Library**: The project uses the [Eigen](https://eigen.tuxfamily.org/) library for linear algebra operations. Download and include it in your project.

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/aaqwesas/MarkovChain_Solver.git
   cd MarkovChain_Solver
   ```
