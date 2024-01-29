#include "Character.h"

Character::Character(int startX, int startY, int initialHealth, int radius)
    : x(startX), y(startY), health(initialHealth), visRadius(radius)
{
    if (initialHealth < 0)
        health = 1;
    else
        health = initialHealth;
    direction = 'w';
    attackRadius = 0;
}

int Character::getX() const
{
    return x;
}

int Character::getY() const
{
    return y;
}

int Character::getHealth() const
{
    return health;
}

int Character::getRadius() const
{
    return visRadius;
}

int Character::getAttackRadius() const {
    return attackRadius;
}
void Character::moveUp()
{
    prevX = x;
    prevY = y;
    
    y--;
    direction = 'w';
}


void Character::moveDown()
{
    prevX = x;
    prevY = y;

    y++;
    direction = 's';
}


void Character::moveLeft()
{   prevX = x;
    prevY = y;

    x--;
    direction = 'a';
}


void Character::moveRight() {
    prevX = x;
    prevY = y;

    x++;
    direction = 'd';
}

void Character::takeDamage(int damage)
{
    health -= damage;
    if (health < 0)
    {
        health = 0;
    }
}


bool Character::isInSight(const Character &other) const
{
    int dx = other.x - x;
    int dy = other.y - y;
    double distance = std::sqrt(dx * dx + dy * dy);
    return distance <= visRadius;
}


bool Character::isInAttackRange(const Character &other, int attackRange) const
{
    int dx = other.x - x;
    int dy = other.y - y;
    double distance = std::sqrt(dx * dx + dy * dy);
    return distance <= attackRange;
}


void Character::moveBack()
{
    x = prevX;
    y = prevY;
}


void Character::lookUp() {
    direction = 'w';
}
void Character::lookDown() {
    direction = 's';
}
void Character::lookLeft() {
    direction = 'a';
}
void Character::lookRight() {
    direction = 'd';
}

char Character::getDirection() {
    return direction;
}