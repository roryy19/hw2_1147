#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <numeric>

void run_morris_algorithm(int n, int k, const std::string& output_file) {
    std::ofstream file(output_file);

    if (!file.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return;
    }

    std::vector<int> exact_count(n);              // Exact count array
    std::vector<std::vector<double>> estimators(n, std::vector<double>(k));  // Matrix to hold k estimators
    std::vector<double> average_estimator(n, 0.0);  // Array to hold the averaged estimator

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Loop to simulate k independent instances of Morris algorithm
    for (int j = 0; j < k; ++j) {
        int X = 0;  // Morris counter initialized to 0 for each instance

        for (int i = 0; i < n; ++i) {
            exact_count[i] = i + 1;  // Exact count increments linearly

            // Morris algorithm: Calculate probability p and compare with random number
            double p = std::pow(0.5, X);
            double r = dis(gen);

            if (r < p) {
                X++;  // Increment Morris counter with probability p
            }

            // Store the estimated count for the current instance
            estimators[i][j] = std::pow(2, X) - 1;
        }
    }

    // Calculate the average estimator (Morris*)
    for (int i = 0; i < n; ++i) {
        // Sum over all k estimators for each event and calculate the average
        double sum = std::accumulate(estimators[i].begin(), estimators[i].end(), 0.0);
        average_estimator[i] = sum / k;
    }

    // Write the results to the output file
    file << "Exact_Count,";
    for (int j = 1; j <= k; ++j) {
        file << "Estimator_" << j << ",";
    }
    file << "Average_Estimator\n";

    for (int i = 0; i < n; ++i) {
        file << exact_count[i] << ",";  // Write exact count

        // Write all k individual estimators
        for (int j = 0; j < k; ++j) {
            file << estimators[i][j] << ",";
        }

        // Write the average estimator
        file << average_estimator[i] << "\n";
    }

    file.close();
    std::cout << "Simulation complete. Results saved to " << output_file << std::endl;
}

int main() {
    int n = 10000;  // Number of events
    int k_values[] = {5, 10, 25, 50, 75, 100};  // Different values of k to try

    // Run the Morris* algorithm for each value of k
    for (int k : k_values) {
        std::string output_file = "morris_star_k_" + std::to_string(k) + ".csv";
        run_morris_algorithm(n, k, output_file);
    }

    return 0;
}
