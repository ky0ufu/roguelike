#include "Enemy.h"

Enemy::Enemy(int startX, int startY, int initialHealth, int visibilityRadius, int dmg)
    : Character(startX, startY, initialHealth, visibilityRadius), damage(dmg) {}


int Enemy::getDamage() const {
    return damage;
}


//bool Enemy::isPlayerInRadius(const Player &player, int radius) const
// {
//     return isInSight(player) && (getX() != player.getX() || getY() != player.getY());
// }

MeleeEnemy::MeleeEnemy(int startX, int startY)
    : Enemy(startX, startY, Balance::MELEE_ENEMY_INITIAL_HEALTH, Balance::ENEMY_VISIBILITY_RADIUS, Balance::ENEMY_MELEE_ATTACK_DAMAGE) {
        attackRadius = Balance::MELEE_WEAPON_RADIUS;
    }   

// void MeleeEnemy::update(Player &player, Map& gameMap)
// {
//     if (isPlayerInRadius(player, Balance::ENEMY_VISIBILITY_RADIUS))
//     {
//         attack(player);
//     }
//     else
//     {
//         randomMove(gameMap);
//     }
// }

// void MeleeEnemy::attack(Player &player)
// {
//     if (isPlayerInRadius(player, Balance::ENEMY_VISIBILITY_RADIUS))
//     {
//         if (isInAttackRange(player, Balance::MELEE_WEAPON_RADIUS))
//         {
//             // Логика атаки ближнего боя
//             player.takeDamage(Balance::ENEMY_MELEE_ATTACK_DAMAGE);
//         }
//     }
// }

RangedEnemy::RangedEnemy(int startX, int startY)
    : Enemy(startX, startY, Balance::RANGE_ENEMY_INITIAL_HEALTH, Balance::ENEMY_VISIBILITY_RADIUS,  Balance::ENEMY_RANGED_ATTACK_DAMAGE) {
        attackRadius = Balance::RANGE_WEAPON_RADIUS;
    }

// void RangedEnemy::update(Player &player, Map& gameMap)
// {
//     if (isPlayerInRadius(player, Balance::ENEMY_VISIBILITY_RADIUS))
//     {
//         attack(player);
//     }
//     else
//     {
//         randomMove(gameMap);
//     }
// }

// void RangedEnemy::attack(Player &player)
// {
//     if (isPlayerInRadius(player, Balance::ENEMY_VISIBILITY_RADIUS))
//     {
//         if (isInAttackRange(player, Balance::RANGE_WEAPON_RADIUS))
//         {
//             // Логика атаки ближнего боя
//             player.takeDamage(Balance::ENEMY_RANGED_ATTACK_DAMAGE);
//         }
//     }
// }

TankEnemy::TankEnemy(int startX, int startY)
    : Enemy(startX, startY, Balance::TANK_ENEMY_INITIAL_HEALTH, Balance::ENEMY_VISIBILITY_RADIUS, Balance::ENEMY_TANK_ATTACK_DAMAGE), turnsToMove(2) {
        attackRadius = Balance::MELEE_WEAPON_RADIUS;
    }


// void TankEnemy::update(Player &player, Map& gameMap)
// {
//     if (turnsToMove == 0)
//     {
//         if (isPlayerInRadius(player, Balance::ENEMY_VISIBILITY_RADIUS))
//         {
//             attack(player);
//         }
//         else
//         {
//             randomMove(gameMap);

//         }
//         turnsToMove = 2;
//     }
//     else
//         turnsToMove--;
// }

// void TankEnemy::attack(Player &player)
// {
//     if (isPlayerInRadius(player, Balance::ENEMY_VISIBILITY_RADIUS))
//     {
//         if (isInAttackRange(player, Balance::MELEE_WEAPON_RADIUS))
//         {
//             // Логика атаки танка
//             player.takeDamage(Balance::ENEMY_TANK_ATTACK_DAMAGE);
//         }
//     }
// }