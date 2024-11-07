#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

std::string removePunctuation(const std::string &word) {
    std::string result;
    for (char c : word) {
        if (!std::ispunct(c)) { // Sprawdzanie, czy dany znak nie jest znakiem interpunkcyjnym
            result += std::tolower(c);
        }
    }
    return result;
}

int main() {
    std::ifstream inputFile("Antek.txt"); 

    if (!inputFile) {
        std::cerr << "Nie można otworzyć pliku." << std::endl;
        return 1;
    }

    std::map<std::string, int> wordFreq;
    std::string word;

    // Wczytywanie słów z pliku i obliczanie ich częstości
    while (inputFile >> word) {
        word = removePunctuation(word);
        if (!word.empty()) {
            wordFreq[word]++;
        }
    }

    inputFile.close();

    // Tworzenie wektora par (słowo, częstość) z mapy
    std::vector<std::pair<std::string, int>> wordFreqVec(wordFreq.begin(), wordFreq.end());

    // Sortowanie wektora według częstości słów
    std::sort(
            wordFreqVec.begin(), wordFreqVec.end(),
              [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
                  return a.second > b.second;
                }
            );

    std::ofstream outputFile("top_words3.txt");
    if (!outputFile) {
        std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
        return 1;
    }

    for (size_t i = 0; i < 20 && i < wordFreqVec.size(); ++i) {
        outputFile << wordFreqVec[i].first << '\t'<< wordFreqVec[i].second << std::endl;
    }

    outputFile.close();

    std::cout << "Pomyślnie zapisano 20 najczęstszych słów do pliku 'top_words.txt'." << std::endl;

    return 0;
}
