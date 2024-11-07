#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <numeric> // std::accumulate

double simulate_walk(int steps, int directions) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> rand_dir(0, directions - 1);

    std::vector<double> x(steps, 0.0);
    std::vector<double> y(steps, 0.0);

    for (int i = 1; i < steps; ++i) {
        double angle = rand_dir(mt) * (2 * M_PI / directions);
        x[i] = x[i - 1] + std::cos(angle);
        y[i] = y[i - 1] + std::sin(angle);
    }

    double msd = x[steps - 1] * x[steps - 1] + y[steps - 1] * y[steps - 1];
    return msd;
}

double calc_diff_coeff(int steps, int num_sim, int directions) {
    std::vector<double> msds(num_sim);

    for (int i = 0; i < num_sim; ++i) {
        msds[i] = simulate_walk(steps, directions);
    }

    double mean_msd = std::accumulate(msds.begin(), msds.end(), 0.0) / num_sim;
    double diff_coeff = mean_msd / (4 * steps);
    return diff_coeff;
}

int main() {
    int steps = 10000;
    int num_simulations = 1000;

    // Oblicz współczynniki dyfuzji dla 4 i 8 kierunków
    double D_4 = calc_diff_coeff(steps, num_simulations, 4);
    double D_8 = calc_diff_coeff(steps, num_simulations, 8);

    std::cout << "Dla 4 kierunków: " << D_4 << std::endl;
    std::cout << "Dla 8 kierunków: " << D_8 << std::endl;

    return 0;
}
