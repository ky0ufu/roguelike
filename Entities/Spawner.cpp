#include "Spawner.h"

MeleeSpawner::MeleeSpawner(int x, int y): x(x), y(y), meleeCount(Balance::MELEE_LOCAL_LIMIT) {}

MeleeEnemy MeleeSpawner::spawn(int x, int y) {
    if(meleeCount > 0) {
        return MeleeEnemy(x, y);
        meleeCount--;
    }
    return MeleeEnemy(-1, -1);
}

RangeSpawner::RangeSpawner(int x, int y): x(x), y(y), rangeCount(Balance::RANGE_LOCAL_LIMIT) {}

RangedEnemy RangeSpawner::spawn(int x, int y) {
    if(rangeCount > 0) {
        return RangedEnemy (x, y);
        rangeCount--;
    }
    return RangedEnemy (-1, -1);
}



TankSpawner::TankSpawner(int x, int y): x(x), y(y), tankCount(Balance::TANK_LOCAL_LIMIT) {}

TankEnemy TankSpawner::spawn(int x, int y) {
    if(tankCount > 0) {
        return TankEnemy(x, y);
        tankCount--;
    }
    return TankEnemy(-1, -1);
}
