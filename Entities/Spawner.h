#include "Enemy.h"
#include "../Balance.h"


class MeleeSpawner {
protected:
    int meleeCount;
    int x;
    int y;

public:
    MeleeEnemy spawn(int x, int y);
    MeleeSpawner(int x, int y);
};

class RangeSpawner {
protected:
    int rangeCount;
    int x;
    int y;


public:
    RangeSpawner(int x, int y);
    RangedEnemy spawn(int x, int y);
};


class TankSpawner {
protected:
    int tankCount;
    int x;
    int y;

public:
    TankSpawner(int x, int y);
    TankEnemy spawn(int x, int y);
};
