#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <ctime>

int main(){

    // Inicjalizacja generatora liczb pseudolosowych
    srand(time(0));

    double dt = 0.01;
    int x = 0;
    int y = 0; 
    int z = 0;
    std::ofstream outputFile("data.txt"); 
    if (!outputFile) {
        std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
        return 1;
    }
    for(int i = 0; i <= 100; i++){ 

        double direct_x = rand() % 3 - 1;
        double direct_y = rand() % 3 - 1;
        double direct_z = rand() % 3 - 1;

        
        x += direct_x;
        y += direct_y;
        z += direct_z;
        
        outputFile << x << '\t' << y << '\t' << z <<'\n';
    }

    outputFile.close(); 
    
    return 0;
}
