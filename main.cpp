#include <iostream>
#include "Entities/Player.h"
#include "Scene/Game.h"

int main()
{
    std::cout << "Hello World!\n";
    Game game = Game();
    game.run();
}
