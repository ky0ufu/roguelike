#pragma once

class Balance {
public:
    // PLAYER SETTINGS
    static const int PLAYER_INITIAL_HEALTH = 100;
    static const int PLAYER_MELEE_AMMO_START = 10;
    static const int PLAYER_RANGED_AMMO_START = 5;
    static const int PLAYER_VISIBILITY_RADIUS = 5;
    static const int PLAYER_MELEE_DAMAGE = 100;
    static const int PLAYER_RANGE_DAMAGE = 15;

    // ENEMY HEALTH
    static const int MELEE_ENEMY_INITIAL_HEALTH = 50;
    static const int RANGE_ENEMY_INITIAL_HEALTH = 25;
    static const int TANK_ENEMY_INITIAL_HEALTH = 75;

    // ENEMY DAMAGE
    static const int ENEMY_MELEE_ATTACK_DAMAGE = 20;
    static const int ENEMY_RANGED_ATTACK_DAMAGE = 15;
    static const int ENEMY_TANK_ATTACK_DAMAGE = 25;

    //RADIUS
    static const int ENEMY_VISIBILITY_RADIUS = 3;
    static const int RANGE_ENEMY_VISIBILITY_RADIUS = 5;

    // KILL POINTS
    static const int MELEE_ENEMY_KILL_POINTS = 10;
    static const int RANGE_ENEMY_KILL_POINTS = 15;
    static const int TANK_ENEMY_KILL_POINTS = 25;

    //WEAPON
    static const int MELEE_WEAPON_RADIUS = 1;
    static const int RANGE_WEAPON_RADIUS = 3;

    // Spawn Limits
    static const int MELEE_LOCAL_LIMIT = 2;
    static const int RANGE_LOCAL_LIMIT = 1;
    static const int TANK_LOCAL_LIMIT = 1;

    static const int MELEE_GLOBAL_LIMIT = 10;
    static const int RANGE_GLOBAL_LIMIT = 5;
    static const int TANK_GLOBAL_LIMIT = 5;

    static const int MELEE_SPAWNERS_LIMIT = 3;
    static const int RANGE_SPAWNERS_LIMIT = 3;
    static const int TANK_SPAWNERS_LIMIT = 3;

    static const int SPAWNER_RADIUS = 4;

};

