#pragma once

#include "level.h"
#include <SFML/Graphics.hpp>

using namespace sf;

enum {
    NEW_GAME,
    PAUSE,
    GAME,
    MENU,
    WIN,
    LOOSE
} gameState;

class Game
{
public:
    Game(int screenWidth, int screenHeight, bool fullScreen, const String &windowName);
    void loadData();
    void initGame();
    void update();
    void draw();
private:
    sf::RenderWindow m_gameWindow;
    Clock m_clock;
    std::vector<Level> m_levels;
};

