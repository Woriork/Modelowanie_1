#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main(){
    double m1 = 1.0;
    double R = 1;
    double vy2 = sqrt(m1/R);
    const int n = 2;
    double x[n] = {0.0, R};
    double y[n] = {0.0, 0.0};
    double vx[n] = {0.0, 0.0};
    double vy[n] = {0.0, vy2};
    double m[n] = {m1, m1};
    double dt = 0.000001;
    double G = 1.0;

    std::ofstream outputFile1("data.txt");
    std::ofstream outputFile2("data2.txt");

    if (!outputFile1 || !outputFile2) {
        std::cerr << "Nie można otworzyć plików do zapisu." << std::endl;
        return 1;
    }

    double max_dt = 0.0;
    double max_dt_error = 0.0;

    for(double t = 0.0; t < 10; t += dt){
        double e ;
        double Fx = 0.0; 
        double Fy = 0.0; 

        // Rozwiązywanie równania ruchu dla wielu ciał
        for(int i = 1; i < n; i++){
            // Obliczanie sił pomiędzy danym ciałem a pozostałymi
            for (int j = 0; j < n ; j++) {
                if (i != j) { 
                    double r = sqrt(pow((x[i]-x[j]), 2) + pow((y[i] - y[j]), 2)); 
                    Fx +=  - G * m[i] * m[j] * (x[i] - x[j]) / pow(r,3);
                    Fy +=  - G * m[i] * m[j] * (y[i] - y[j]) / pow(r,3);
                }
            } 
            vx[i] += Fx * t / m[i];
            vy[i] += Fy * t / m[i];
            x[i] += t * vx[i];
            y[i] += t * vy[i];

            double r = sqrt(pow(x[0] - x[1], 2) + pow(y[0] - y[1], 2));
            e = abs(R - r);
        }
        outputFile2 << t << '\t' << e << endl;
        outputFile1 << x[0] << '\t' << y[0] << '\t' << x[1] << '\t' << y[1] << endl;
    }

    outputFile1.close();
    outputFile2.close();
    return 0;
}
