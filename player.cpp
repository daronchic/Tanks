#include "player.h"

Player::Player(const Image &image, const String &name, Level &level, float x, float y, int width, int height) :
    Entity(image, name, x, y, width, height), m_state(STAY), m_score(0)
{
    /*TODO: set sprite from tileset
    * if(m_name = "Player_1")
    *   m_sprite.setTexture(IntRect(0, 0, m_width, m_height));
    *
    *
    */
    this->m_object = level.getAllObjects();
}

void Player::control()
{
    if(Keyboard::isKeyPressed) {
        if(Keyboard::isKeyPressed(Keyboard::Left))
            m_state = LEFT;
        if(Keyboard::isKeyPressed(Keyboard::Up))
            m_state = UP;
        if(Keyboard::isKeyPressed(Keyboard::Right))
            m_state = RIGHT;
        if(Keyboard::isKeyPressed(Keyboard::Down))
            m_state = DOWN;
        if(Keyboard::isKeyPressed(Keyboard::Space))
            m_state = SHOOT;
    }
}

void Player::checkCollisionsWithMap()
{

}

void Player::update(float time)
{

}
