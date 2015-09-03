#include "game.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    Game game(800, 600, false, "The Tanks!");
    game.loadData();
    game.initGame();
    game.update();
    return 0;
}
