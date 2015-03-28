#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(0));

    try {
        Game game;
        game.run();
    }
    catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
