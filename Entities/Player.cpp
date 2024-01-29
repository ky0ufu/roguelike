#include "Player.h"

Player::Player(int startX, int startY)
    : Character(startX, startY, Balance::PLAYER_INITIAL_HEALTH, Balance::PLAYER_VISIBILITY_RADIUS),
      killPoints(0), rangedAmmo(Balance::PLAYER_RANGED_AMMO_START) {
        meleeDmg = Balance::PLAYER_MELEE_DAMAGE;
        rangeDmg = Balance::PLAYER_RANGE_DAMAGE;
        attackRadius = Balance::MELEE_WEAPON_RADIUS;
      }

void Player::displayInfo() const {
    std::cout << "Health: " << getHealth() << " | Kill Points: " << killPoints
              << " | Ranged Ammo: " << rangedAmmo << std::endl;
}

int Player::getAmmo() const {
    return rangedAmmo;
}
int Player::getPoints() const {
    return killPoints;
}

int Player::getDmg() const {
    return dmg;
}

int Player::getRange() const {
    return rangeDmg;
}

void Player::pickUpRangedAmmo(int amount) {
    rangedAmmo += amount;
}

void Player::pickUpHealthKit(int amount) {
    takeDamage(-amount);  // Восстановление здоровья
}

void Player::meleeAttack(Enemy& enemy) {
    // Реализация атаки для Player
    if (isInAttackRange(enemy, Balance::MELEE_WEAPON_RADIUS)) {
        // Логика ближней атаки
        enemy.takeDamage(Balance::PLAYER_MELEE_DAMAGE);
    }
}

void Player::rangeAttack(Enemy& enemy) {
    if (isInAttackRange(enemy, Balance::RANGE_WEAPON_RADIUS) && rangedAmmo > 0) {
        // Логика дальней атаки
        enemy.takeDamage(Balance::ENEMY_RANGED_ATTACK_DAMAGE);
        rangedAmmo--;
    }
}
void Player::switchGun() {
    if (dmg == meleeDmg) {
        dmg = rangeDmg;
        attackRadius = Balance::RANGE_WEAPON_RADIUS;
    }
    else {
        dmg = meleeDmg;
        attackRadius = Balance::MELEE_WEAPON_RADIUS;
    }
}

void Player::attack(Enemy& enemy) {
    if (dmg == meleeDmg)
        meleeAttack(enemy);
    else {
        rangeAttack(enemy);
    }
}