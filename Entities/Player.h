#pragma once
#include "Character.h"
#include "../Balance.h"
#include "Enemy.h"
#include <iostream>

class Player : public Character {
private:
    int killPoints; // количество очков за убийство
    int rangedAmmo; // количество снарядов дальнего боя
    int rangeDmg;
    int meleeDmg;
    int dmg;

public:
    Player(int startX, int startY);

    void displayInfo() const;
    int getAmmo() const;
    int getPoints() const;

    int getMelee() const;
    int getRange() const;

    void switchGun();
    int getDmg() const;
    void attack(Enemy& enemy);

    // Методы для взаимодействия с предметами
    void pickUpRangedAmmo(int amount);
    void pickUpHealthKit(int amount);

    void meleeAttack(Enemy& enemy);

    void rangeAttack(Enemy& enemy);
    // Дополнительные методы и поля можно добавить по мере необходимости
};
