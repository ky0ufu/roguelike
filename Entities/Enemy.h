#pragma once

#include "Character.h"
#include "../Balance.h"
#include <cstdlib>
#include <ctime>

class Enemy : public Character {
public:
    Enemy(int startX, int startY, int initialHealth, int visibilityRadius, int damage);
    int getDamage() const;


protected:
    int damage;
    // void randomMove(Map& gameMap);

    // bool isPlayerInRadius(const Player& player, int radius) const;
};


class MeleeEnemy : public Enemy {
public:
    MeleeEnemy(int startX, int startY);
    

};

class RangedEnemy : public Enemy {
public:
    RangedEnemy(int startX, int startY);

};

class TankEnemy : public Enemy {
private:
    int turnsToMove;  // Ходы до следующего движения

public:
    TankEnemy(int startX, int startY);

};

