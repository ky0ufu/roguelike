#pragma once
#include "Map.h"
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <future>
#include <ncurses.h>
#include "../Balance.h"
#include "../Entities/Spawner.h"
#include "../Entities/SpawnManager.h"

class Game {
private:
    Map gameMap;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<MeleeSpawner> meleeSpawners;
    std::vector<RangeSpawner> rangeSpawners;
    std::vector<TankSpawner> tankSpawners;
    GlobalSpawenerManager spawnManager;


public:
    Game();

    void run();  // Метод для запуска игры


private:
    void fight();

    void createMeleeSpawner();
    void createRangeSpawner();
    void createTankSpawner();

    int randomX();
    int randomY();

    void spawnMelee();
    void spawnRange();
    void spawnTank();

    void spawnEnemies();
    //void updateEnemies();  // Метод для обновления врагов

    // Player movement
    int handleInput();

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();

    void switchWeapon();

    // Player attack
    void playerAttack();

    void attackRight(int radius);
    void attackLeft(int radius);
    void attackUp(int radius);
    void attackDown(int radius);

    void attackEnemy(int x, int y);
    
    // Enemies attack
    void attacked();

    bool enemyAttackUp(const Enemy& enemy);

    bool enemyAttackDown(const Enemy& enemy);

    bool enemyAttackLeft(const Enemy& enemy);

    bool enemyAttackRight(const Enemy& enemy);

    // Enemies movement 
    void randomMove(Enemy& enemy);

    void enemyMoveUp(Enemy& enemy);

    void enemyMoveDown(Enemy& enemy);

    void enemyMoveRight(Enemy& enemy);

    void enemyMoveLeft(Enemy& enemy);

    void enemiesRandomMove();
};
