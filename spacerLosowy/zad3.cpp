#include <fstream> 
#include <ctime> 
#include <iostream> 
#include <random> 
using namespace std; 
  
int main() 
{ 
    //tablica wystapien krokow koncowych - indeks to dany krok końcowy
    //wartość jest zbyt duża przez problemy z wychodzeniem poza zakres 
    int arr_mt[1'000] = {0};

    mt19937 mt(time(nullptr)); 
    uniform_int_distribution<int> random(0, 1);
    srand(time(NULL));


    std::ofstream outputFile("data3.txt");
        if (!outputFile) {
            std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
            return 1;} 


    //ilość spacerów
    for (int j = 0; j < 1'000'0; j++){
        int mrt = 0;
        //obliczenie kroku koncowego - odległości od startu
        for(int i = 0; i <= 1'000; i++){ 
            mrt += (random(mt) == 1) ? -1 : 1;

        }
        //gdy krok końcowy sie powtorzy wartosc pod indeksem kroku zostaje zwiekszona o 1 dzieki czemu mozna zliczyc wystapienia
        arr_mt[abs(mrt)]++;
    }
  
  for(int i = 0; i < 30; i++){
    outputFile << i + 1  << '\t' << arr_mt[i] <<'\n';
  }
  
  outputFile.close(); 
  return 0; 
}