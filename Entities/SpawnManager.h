#include "Enemy.h"

class GlobalSpawenerManager {
protected:
    int globalTankCount;
    int globalRangeCount; 
    int globalMeleeCount;
public:
    GlobalSpawenerManager();

    void canSpawnMelee();
    void canSpawnRange();
    void canSpawnTank();

    int meleeLimit() const;
    int rangeLimit() const;
    int tankLimit() const;

};