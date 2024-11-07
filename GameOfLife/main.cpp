#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

const int len = 100;
const int duration = 100;

// Inicjalizacja siatki i tablicy tymczasowej
int grid[len][len];
int tmp[len][len];

void initializeGrid() {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
}

int count(int i, int j) {
    int sum = 0;
    int up, down, right, left;
    if(i < len - 1) down = i + 1; else down = 0;
    if(i > 0 ) up = i - 1; else up = len - 1;
    if(j < len - 1) right = j + 1; else right = 0;
    if(j > 0 ) left = j - 1; else left = len - 1;
    sum = grid[down][j] + grid[up][j] + grid[i][right] + grid[i][left] +
            grid[down][right] + grid[down][left] + grid[up][right] + grid[up][left];
    return sum;
}
int step() {
    int density = 0;
    int neig_sum = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            int s = count(i,j);
            if(s == 2|| s == 3) tmp[i][j] = 1;
            else tmp[i][j] = 0;
            density += tmp[i][j];
            }
            
        }
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            grid[i][j] = tmp[i][j];
        }
    }
    return density;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(len, len), "Game of Life");

    initializeGrid();

    // Główna pętla aplikacji
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        int density = step();

        window.clear(sf::Color::Black);

        // Renderowanie siatki
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                sf::RectangleShape rectangle(sf::Vector2f(1, 1));
                rectangle.setPosition(i, j);
                if (tmp[i][j] == 1) {
                    rectangle.setFillColor(sf::Color::Black);
                } else {
                    rectangle.setFillColor(sf::Color::White);
                }
                window.draw(rectangle);
            }
        }

        window.display();
        Sleep(100);
    }

    return 0;
}
