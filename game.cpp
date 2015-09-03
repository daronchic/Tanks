#include "game.h"
#include "view.h"

Game::Game(int screenWidth, int screenHeight, bool fullScreen, const String &windowName)
{
    m_gameWindow.create(sf::VideoMode(screenWidth, screenHeight), windowName);
    gameState = NEW_GAME;
}

void Game::loadData()
{

}

void Game::initGame()
{

}

void Game::update()
{
    while (m_gameWindow.isOpen()) {
        Event event;
        float time = m_clock.getElapsedTime().asMicroseconds();

        m_clock.restart();
        time = time / 800;

        while (m_gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_gameWindow.close();
        }
        draw();
    }
}

void Game::draw()
{
    m_gameWindow.setView(playerView);
    m_gameWindow.clear(Color(77,83,140));
    m_gameWindow.display();
}

