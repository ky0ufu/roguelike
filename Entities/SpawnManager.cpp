#include "SpawnManager.h"

GlobalSpawenerManager::GlobalSpawenerManager() : globalMeleeCount(Balance::MELEE_GLOBAL_LIMIT),
                                                 globalRangeCount(Balance::RANGE_GLOBAL_LIMIT),
                                                 globalTankCount(Balance::TANK_GLOBAL_LIMIT) {}



void GlobalSpawenerManager::canSpawnMelee() {
    if (globalMeleeCount > 0) {
        globalMeleeCount--;

    }
}

void GlobalSpawenerManager::canSpawnRange() {
    if (globalRangeCount > 0) {
        globalRangeCount--;
    }

}

void GlobalSpawenerManager::canSpawnTank() {
    if (globalTankCount > 0) {
        globalTankCount--;
    }
}

int GlobalSpawenerManager::meleeLimit() const {
    return globalMeleeCount;
}

int GlobalSpawenerManager::rangeLimit() const {
    return globalRangeCount;
}

int GlobalSpawenerManager::tankLimit() const {
    return globalTankCount;
}
