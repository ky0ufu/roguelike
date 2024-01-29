#include "Game.h"
// Для функции rand()

Game::Game() : gameMap(Map(5, 8)), player(Player(1, 1)), spawnManager(GlobalSpawenerManager())
{
    MeleeEnemy enemy = MeleeEnemy(5, 5);
    enemies.push_back(enemy);
    gameMap.setBlockType(enemy.getX(), enemy.getY(), 'E');


    for (int i = 0; i < Balance::MELEE_SPAWNERS_LIMIT; i++)
        createMeleeSpawner();

    for (int i = 0; i < Balance::RANGE_SPAWNERS_LIMIT; i++)
        createRangeSpawner();

    for (int i = 0; i < Balance::TANK_SPAWNERS_LIMIT; i++)
        createTankSpawner();
}

void Game::createMeleeSpawner()
{
    int x = randomX();
    int y = randomY();

    while (gameMap.getBlockType(x, y) != ' ')
    {
        x = randomX();
        y = randomY();
    }
    meleeSpawners.push_back(MeleeSpawner(x, y));
    gameMap.setBlockType(x, y, 'm');
}

void Game::createRangeSpawner()
{
    int x = randomX();
    int y = randomY();

    while (gameMap.getBlockType(x, y) != ' ')
    {
        x = randomX();
        y = randomY();
    }
    rangeSpawners.push_back(RangeSpawner(x, y));
    gameMap.setBlockType(x, y, 'r');
}

void Game::createTankSpawner()
{
    int x = randomX();
    int y = randomY();

    while (gameMap.getBlockType(x, y) != ' ')
    {
        x = randomX();
        y = randomY();
    }
    tankSpawners.push_back(TankSpawner(x, y));
    gameMap.setBlockType(x, y, 't');
}

// void asyncInput(Game &game, bool &inputThreadRunning)
// {
//     while (inputThreadRunning)
//     {
//         game.handleInput();
//     }
// }
int Game::randomX()
{
    return rand() % (gameMap.getCols() - 5 + 1) + 5;
}
int Game::randomY()
{
    return rand() % (gameMap.getRows() - 5 + 1) + 5;
}

void Game::run()
{
    bool inputThreadRunning = true;
    initscr();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    noecho();
    timeout(200);
    // Async Input
    // std::future<void> inputFuture = std::async(std::launch::async, asyncInput, std::ref(*this), std::ref(inputThreadRunning));

    resize_term(1900, 1080);
    int turn = 0;
    while (player.getHealth() > 0)
    {
        // auto start = std::chrono::high_resolution_clock::now();

        // Обновление и отображение карты
        // spawnEnemies();
        // updateEnemies();
        gameMap.display(player, enemies);
        // Вывод информации об игроке в консоль
        int ch = handleInput();
        if (ch == ' ')
        {
            playerAttack();
        }
        turn++;
        if (turn % 6 == 0)
        {
            enemiesRandomMove();
        }
        if (turn % 10 == 0)
            spawnEnemies();

        attacked();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(35));
    }
    // handleInput();

    //
    // inputThreadRunning = false;

    // inputFuture.get();

    // Конец игры
    clear();
    gameMap.gameOver();
    getch();
    endwin();
}

// void Game::spawnEnemies() {
//     // Логика спавна врагов
//     // Можно настроить параметры спавна врагов здесь
//     // Пример спавна случайного врага
//     if (rand() % 100 < 10) {  // Вероятность спавна врага 10%
//         int x = rand() % gameMap.getCols();
//         int y = rand() % gameMap.getRows();
//         enemies.push_back(Enemy(x, y));
//     }
// }

// void Game::updateEnemies() {
//     // Логика обновления врагов
//     // Можно добавить дополнительные действия врагов здесь
//     for (auto& enemy : enemies) {
//         enemy.update(gameMap, player);
//     }
// }

void Game::movePlayerUp()
{
    player.lookUp();
    const int y = player.getY();
    const int x = player.getX();
    if (y - 1 >= 0 && gameMap.getBlockType(x, y - 1) == ' ')
        player.moveUp();
}

void Game::movePlayerDown()
{
    player.lookDown();
    const int y = player.getY();
    const int x = player.getX();
    if (y + 1 < gameMap.getRows() && gameMap.getBlockType(x, y + 1) == ' ')
        player.moveDown();
}

void Game::movePlayerLeft()
{

    const int y = player.getY();
    const int x = player.getX();
    player.lookLeft();
    if (x - 1 >= 0 && gameMap.getBlockType(x - 1, y) == ' ')
        player.moveLeft();
}

void Game::movePlayerRight()
{
    player.lookRight();
    const int y = player.getY();
    const int x = player.getX();
    if (x + 1 < gameMap.getCols() && gameMap.getBlockType(x + 1, y) == ' ')
        player.moveRight();
}

int Game::handleInput()
{
    int ch = getch();
    if (ch == 'w' || ch == 'W')
    {
        movePlayerUp();
        return ch;
    }
    if (ch == 's' || ch == 'S')
    {
        movePlayerDown();
        return ch;
    }

    if (ch == 'a' || ch == 'A')
    {
        movePlayerLeft();
        return ch;
    }

    if (ch == 'd' || ch == 'D')
    {
        movePlayerRight();
        return ch;
    }

    return ch;
}

void Game::playerAttack()
{
    const char direction = player.getDirection();
    const int radius = player.getAttackRadius();
    player.pickUpHealthKit(100);

    switch (direction)
    {
    case 'w':
        attackUp(radius);
        break;

    case 's':
        attackDown(radius);
        break;

    case 'a':
        attackLeft(radius);
        break;
    case 'd':
        attackRight(radius);
        break;

    default:
        break;
    }
}

void Game::attackUp(int radius)
{
    const int playerX = player.getX();
    const int playerY = player.getY();

    for (int i = playerY - 1; i >= 0; i--)
    {
        if (std::abs(playerY - i) > radius)
            break;
        if (gameMap.getBlockType(playerX, i) == 'E')
        {
            attackEnemy(playerX, i);
            break;
        }
        if (gameMap.getBlockType(playerX, i) != ' ' && gameMap.getBlockType(playerX, i) != 'E')
            break;
    }
}

void Game::attackDown(int radius)
{
    const int playerX = player.getX();
    const int playerY = player.getY();
    for (int i = playerY + 1; i < gameMap.getRows(); i++)
    {
        if (std::abs(playerY - i) > radius)
            break;

        if (gameMap.getBlockType(playerX, i) == 'E')
        {
            attackEnemy(playerX, i);
            break;
        }
        if (gameMap.getBlockType(playerX, i) != ' ' && gameMap.getBlockType(playerX, i) != 'E')
            break;
    }
}

void Game::attackLeft(int radius)
{

    const int playerX = player.getX();
    const int playerY = player.getY();
    for (int i = playerX - 1; i >= 0; i--)
    {
        if (std::abs(playerX - i) > radius)
            break;

        if (gameMap.getBlockType(i, playerY) == 'E')
        {
            attackEnemy(i, playerY);
            break;
        }
        if (gameMap.getBlockType(i, playerY) != ' ')
            break;
    }
}

void Game::attackRight(int radius)
{
    const int playerX = player.getX();
    const int playerY = player.getY();
    player.pickUpHealthKit(100);
    for (int i = playerX + 1; i < gameMap.getCols(); i++)
    {
        if (std::abs(playerX - i) > radius)
            break;

        if (gameMap.getBlockType(i, playerY) == 'E')
        {
            attackEnemy(i, playerY);
            break;
        }
        if (gameMap.getBlockType(i, playerY) != ' ')
            break;
    }
}

void Game::attackEnemy(int x, int y)
{
    const int meleeDamage = player.getDmg();
    static const int attackRange = player.getAttackRadius();
    refresh();
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (it->getX() == x && it->getY() == y && ::abs(y - player.getY()) <= attackRange && std::abs(x - player.getX()) <= attackRange)
        {
            it->takeDamage(meleeDamage);
            if (it->getHealth() <= 0)
                enemies.erase(it);
        }
    }
}

void Game::attacked()
{
    const int playerX = player.getX();
    const int playerY = player.getY();

    for (Enemy &enemy : enemies)
    {
        char direction = enemy.getDirection();

        auto enemy_type = typeid(enemy).name();
        const int enemy_radius = enemy.getRadius();

        if (std::abs(enemy.getY() - playerY) <= enemy_radius && std::abs(enemy.getX() - playerX) <= enemy_radius)
        {

            if (enemyAttackUp(enemy))
                continue;

            if (enemyAttackDown(enemy))
                continue;

            if (enemyAttackLeft(enemy))
                continue;

            if (enemyAttackRight(enemy))
                continue;
        }
    }
}

bool Game::enemyAttackUp(const Enemy &enemy)
{
    const int radius = enemy.getAttackRadius();
    const int playerX = player.getX();
    const int playerY = player.getY();

    if (playerX == enemy.getX() && enemy.getY() - playerY <= radius && enemy.getY() - playerY > 0)
    {
        for (int i = enemy.getY() - 1; i >= playerY; i--)
        {

            if (i == playerY)
            {
                player.takeDamage(enemy.getDamage());
                return true;
            }
            if (gameMap.getBlockType(playerX, i) != ' ')
            {
                player.pickUpHealthKit(i);
                break;
            }
        }
    }
    return false;
}

bool Game::enemyAttackDown(const Enemy &enemy)
{
    const int radius = enemy.getRadius();
    const int playerX = player.getX();
    const int playerY = player.getY();

    if (playerX == enemy.getX() && playerY - enemy.getY() <= radius && playerY - enemy.getY() > 0)
        for (int i = enemy.getY() + 1; i <= playerY; i++)
        {

            if (i == playerY)
            {
                player.takeDamage(enemy.getDamage());
                return true;
            }
            if (gameMap.getBlockType(playerX, i) != ' ')
                break;
        }
    return false;
}

bool Game::enemyAttackLeft(const Enemy &enemy)
{
    const int radius = enemy.getRadius();
    const int playerX = player.getX();
    const int playerY = player.getY();

    if (playerY == enemy.getY() && enemy.getX() - playerX <= radius && enemy.getX() - playerX > 0)
        for (int i = enemy.getX() - 1; i >= playerY; i--)
        {

            if (i == playerX)
            {
                player.takeDamage(enemy.getDamage());
                return true;
            }
            if (gameMap.getBlockType(i, playerY) != ' ')
                break;
        }
    return false;
}

bool Game::enemyAttackRight(const Enemy &enemy)
{
    const int radius = enemy.getRadius();
    const int playerX = player.getX();
    const int playerY = player.getY();

    if (playerY == enemy.getY() && playerX - enemy.getX() <= radius && playerX - enemy.getX() > 0)
        for (int i = enemy.getX() + 1; i <= playerY; i--)
        {

            if (i == playerX)
            {
                player.takeDamage(enemy.getDamage());
                return true;
            }
            if (gameMap.getBlockType(i, playerY) != ' ')
                break;
        }
    return false;
}

void Game::randomMove(Enemy &enemy)
{
    int randomDirection = rand() % 4; // 0 - up, 1 - down, 2 - left, 3 - right

    switch (randomDirection)
    {
    case 0:
        enemyMoveUp(enemy);
        break;
    case 1:
        enemyMoveDown(enemy);
        break;
    case 2:
        enemyMoveLeft(enemy);
        break;
    case 3:
        enemyMoveRight(enemy);
        break;
    default:
        break;
    }
}

void Game::enemyMoveUp(Enemy &enemy)
{
    enemy.lookUp();
    const int y = enemy.getY();
    const int x = enemy.getX();
    const int playerX = player.getX();
    const int playerY = player.getY();

    if (y - 1 >= 0 && gameMap.getBlockType(x, y - 1) == ' ' && playerX != x && playerY != y + 1)
    {
        gameMap.setBlockType(x, y, ' ');
        gameMap.setBlockType(x, y - 1, 'E');
        enemy.moveUp();
    }
}

void Game::enemyMoveDown(Enemy &enemy)
{
    enemy.lookDown();
    const int y = enemy.getY();
    const int x = enemy.getX();
    const int playerX = player.getX();
    const int playerY = player.getY();

    if (y + 1 < gameMap.getRows() && gameMap.getBlockType(x, y + 1) == ' ' && playerX != x && playerY != y + 1)
    {
        gameMap.setBlockType(x, y, ' ');
        gameMap.setBlockType(x, y + 1, 'E');
        enemy.moveDown();
    }
}

void Game::enemyMoveLeft(Enemy &enemy)
{
    enemy.lookLeft();
    const int y = enemy.getY();
    const int x = enemy.getX();
    const int playerX = player.getX();
    const int playerY = player.getY();

    if (x - 1 >= 0 && gameMap.getBlockType(x - 1, y) == ' ' && playerX != x - 1 && playerY != y)
    {
        gameMap.setBlockType(x, y, ' ');
        gameMap.setBlockType(x - 1, y, 'E');
        enemy.moveLeft();
    }
}

void Game::enemyMoveRight(Enemy &enemy)
{
    enemy.lookRight();
    const int y = enemy.getY();
    const int x = enemy.getX();
    const int playerX = player.getX();
    const int playerY = player.getY();

    if (x + 1 < gameMap.getCols() && gameMap.getBlockType(x + 1, y) == ' ' && playerX != x + 1 && playerY != y)
    {
        gameMap.setBlockType(x, y, ' ');
        gameMap.setBlockType(x + 1, y, 'E');
        enemy.moveRight();
    }
}

void Game::enemiesRandomMove()
{

    for (Enemy &enemy : enemies)
    {
        randomMove(enemy);
    }
}

void Game::spawnMelee()
{
    for (MeleeSpawner &spawner : meleeSpawners)
    {
        int x = randomX();
        int y = randomY();
        if (spawnManager.meleeLimit() > 0)
        {
            while (gameMap.getBlockType(x, y) != ' ')
            {
                x = randomX();
                y = randomY();
            }
            auto enemy = spawner.spawn(x, y);
            spawnManager.canSpawnMelee();
            if (enemy.getX() > 0 && enemy.getY() > 0 && enemy.getY() < gameMap.getRows() && enemy.getX() < gameMap.getCols())
                enemies.push_back(enemy);
        }
    }
}

void Game::spawnRange()
{
    for (RangeSpawner &spawner : rangeSpawners)
    {
        int x = randomX();
        int y = randomY();
        if (spawnManager.rangeLimit() > 0)
        {
            while (gameMap.getBlockType(x, y) != ' ')
            {
                x = randomX();
                y = randomY();
            }
            auto enemy = spawner.spawn(x, y);
            spawnManager.canSpawnRange();
            if (enemy.getX() > 0 && enemy.getY() > 0 && enemy.getY() < gameMap.getRows() && enemy.getX() < gameMap.getCols())
                enemies.push_back(enemy);

        }
    }
}

void Game::spawnTank()
{
    for (TankSpawner &spawner : tankSpawners)
    {
        int x = randomX();
        int y = randomY();
        if (spawnManager.tankLimit() > 0)
        {
            while (gameMap.getBlockType(x, y) != ' ')
            {
                x = randomX();
                y = randomY();
            }
            auto enemy = spawner.spawn(x, y);
            spawnManager.canSpawnTank();
            if (enemy.getX() > 0 && enemy.getY() > 0 && enemy.getY() < gameMap.getRows() && enemy.getX() < gameMap.getCols())
                enemies.push_back(enemy);
        }
    }
}

void Game::spawnEnemies()
{
    spawnTank();
    spawnRange();
    spawnMelee();
}

void Game::switchWeapon() {

}