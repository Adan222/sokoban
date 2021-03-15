#include "Game.hpp"
#include <iostream>
#include <filesystem>

int main()
{
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';

    Game game;
    game.run();
    return 0;
}
