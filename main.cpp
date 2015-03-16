#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(0));

    std::cout << " 1| P1 vs P2\n"
              << " 2| P1 vs AI\n"
              << " 3| AI vs AI\n";

    Game game;
    game.run();

    return 0;
}
