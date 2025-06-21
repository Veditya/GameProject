#include "../headers/Game.h"
#include <iostream>

int main()
{
    std::cout << "__cplusplus = " << __cplusplus << "\n"; // version of c++
    Game game;
    game.run();
    return 0;
}