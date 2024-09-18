#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>

int main() {
    const int n = 10000;           // Total number of events
    std::vector<double> exact_count(n);
    std::vector<double> estimated_count(n);
    int X = 0;                     // Morris counter initialized to 0

    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Morris Algorithm Simulation
    for (int i = 0; i < n; ++i) {
        // Update exact count
        exact_count[i] = i + 1;

        // Calculate probability p
        double p = pow(0.5, X);

        // Generate a random number between 0 and 1
        double r = dis(gen);

        // Update Morris counter X with probability p
        if (r < p) {
            X += 1;
        }

        // Estimate the count using the Morris Algorithm
        estimated_count[i] = pow(2, X) - 1;
    }

    // Write data to files for plotting
    std::ofstream exact_file("exact_count.txt");
    std::ofstream estimated_file("estimated_count.txt");

    for (int i = 0; i < n; ++i) {
        exact_file << exact_count[i] << "\n";
        estimated_file << estimated_count[i] << "\n";
    }

    exact_file.close();
    estimated_file.close();

    std::cout << "Simulation complete. Data saved to files." << std::endl;

    return 0;
}
