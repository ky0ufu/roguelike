#pragma once
#include <vector>
#include <iostream>
#include <ncurses.h>
#include "../Entities/Player.h"  // Включаем Character, чтобы использовать его взаимодействие с блоками
#include "../Entities/Enemy.h"
#include <string> 
class Map {
private:
    std::vector<std::vector<char>> blocks;  // двумерный вектор для хранения блоков карты
    int rows;  // количество строк на карте
    int cols;  // количество столбцов на карте

public:
    Map(int numRows, int numCols);

    void display(const Player& player, const std::vector<Enemy>& enemies) const;
    char getBlockType(int x, int y) const;

    // Дополнительные методы для работы с картой
    void setBlockType(int x, int y, const char blockType);

    int getRows() const;
    int getCols() const;

    void gameOver() const;
};
