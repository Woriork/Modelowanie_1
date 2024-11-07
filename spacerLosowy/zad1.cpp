#include <fstream> 
#include <ctime> 
#include <iostream> 
#include <random> 
using namespace std; 
  
int main() 
{ 
    int arr_rand[10'000] = {0};
    int arr_mt[10'000] = {0};

    mt19937 mt(time(nullptr)); 
    uniform_real_distribution<float> random(0, 1.0);
    srand(time(NULL));


    std::ofstream outputFile("data1.txt");
        if (!outputFile) {
            std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
            return 1;} 



    
    for(int i = 0; i <= 1'000'000; i++){ 
        int rd = int(floor((rand())/float(RAND_MAX)*10'000));
        int mrt = int(floor(random(mt)*10'000));
        arr_rand[rd]++;
        arr_mt[mrt]++;
    }
  
  for(int i = 0; i < 10'000; i++){
    outputFile << i + 1 << '\t' << arr_rand[i] << '\t' << arr_mt[i] <<'\n';
  }
  cout << mt() % 10'000 << '\n';  
  cout << int(floor(rand()/float(RAND_MAX + 1)*10'000)) << '\n';
  cout << rand() % 10'000 << "\n";
  cout << random(mt)*10'000 << '\n';
  outputFile.close(); 
  return 0; 
}