#pragma once
#include <string>
#include <vector>
#include <cmath>

class Character {
protected:
    int x;
    int y;
    int health;
    int visRadius;
    int prevX;
    int prevY;
    char direction;
    int attackRadius;

public:
    Character(int startX, int startY, int initialHealth, int radius);
    
    int getX() const;
    int getY() const;
    int getHealth() const;
    int getRadius() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    int getAttackRadius() const;
    void takeDamage(int damage);

    bool isInSight(const Character& other) const;

    bool isInAttackRange(const Character& other, int attackRange) const;

    void moveBack();

    void lookUp();
    void lookDown();
    void lookLeft();
    void lookRight();

    char getDirection();
};  



