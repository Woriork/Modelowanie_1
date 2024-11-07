#include <iostream>
#include <cmath>
#include <fstream>

void save_to_txt(const std::string& filename, int nr, double x, double y) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << nr << " " << x << " " << y << "\n";
        file.close();
    } else {
        std::cerr << "Error occurred while saving data to " << filename << std::endl;
    }
}

void clear_data(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file.close();
    } else {
        std::cerr << "Error occurred while clearing data in " << filename << std::endl;
    }
}

int main() {
    // Dane
    double m[] = {1, 1};
    double G = 1;
    double R = 1;
    double Tmax = 5;
    double dt = 0.000035;
    int N = 2; // Liczba ciał

    // Prędkości
    double V[] = {sqrt(pow(m[1], 2) / (m[0] + m[1])), 0.05, 0.25};
    for (double v = 0.0; v <= 1.0; v += 0.1) {
        V.push_back(round(v, 2));
    }

    // Nr wykresu do zapisu wykresów
    int nr = 0;

    // Clears error_data.txt file
    clear_data("error_data.txt");
    clear_data("diameters.txt");

    for (double v : V) {
        // Clears data.txt file before writing new data
        clear_data("data.txt");
        // Położenia ciał
        double X[] = {0, 1};
        double Y[] = {0, 0};

        // Prędkości
        double vx[] = {0, 0};
        double vy[] = {-v, v};

        // Save initial coordinates of bodies
        for (int i = 0; i < N; ++i) {
            save_to_txt("data.txt", i, X[i], Y[i]);
        }

        for (double t = 0.0; t <= Tmax; t += dt) {
            for (int i = 0; i < N; ++i) {
                double Fx = 0;
                double Fy = 0;
                for (int j = 0; j < N; ++j) {
                    if (j != i) {
                        double rx = X[j] - X[i];
                        double ry = Y[j] - Y[i];
                        double r_mod = sqrt(rx * rx + ry * ry);
                        Fx += G * (m[i] * m[j]) / (r_mod * r_mod) * rx / r_mod;
                        Fy += G * (m[i] * m[j]) / (r_mod * r_mod) * ry / r_mod;
                        vx[i] += Fx * dt / m[i];
                        vy[i] += Fy * dt / m[i];
                        X[i] += vx[i] * dt;
                        Y[i] += vy[i] * dt;
                    }
                }
                save_to_txt("data2.txt", i, X[i], Y[i]);
            }
        }

        ++nr;
    }

    return 0;
}
