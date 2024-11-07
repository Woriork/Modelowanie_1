#include <fstream> 
#include <ctime> 
#include <iostream> 
#include <random> 
#include <vector>
#include <algorithm> // std::all_of
using namespace std; 
  
int main() 
{ 
    mt19937 mt(time(nullptr)); 
    uniform_int_distribution<int> random(0, 1);

    std::ofstream outputFile("data4.txt");
    if (!outputFile) {
        std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
        return 1;
    } 

    // Wymiary przestrzeni
    vector<int> dimensions = {1, 2, 3};

    for (int d : dimensions) {
        int successes = 0; // Liczba sukcesów, gdy dziecko wróci do punktu wyjścia
        const int trials = 1000; // Ilość prób

        // 1000 spacerów o długości 1000 kroków w danym wymiarze
        for (int j = 0; j < trials; ++j) {
            vector<int> position(d, 0); // Pozycja dziecka w danym wymiarze
            bool returned_to_start = false; 

            for(int i = 0; i < 1000; ++i) { 
                for (int dim = 0; dim < d; ++dim) {
                    position[dim] += (random(mt) == 1) ? -1 : 1;
                }

                if (std::all_of(position.begin(), position.end(), [](int x) { return x == 0; })) {
                    returned_to_start = true;
                    break;
                }
            }

            if (returned_to_start) {
                ++successes;
            }
        }

        double probability = static_cast<double>(successes) / trials;
        outputFile << "Wymiar przestrzeni: " << d << ", Prawdopodobieństwo: " << probability << '\n';
    }

    outputFile.close(); 
    return 0; 
}
