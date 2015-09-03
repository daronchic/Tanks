#include "entity.h"

Entity::Entity(const Image &image, const String &name, float x, float y, int width, int height) :
    m_directionX(0), m_directionY(0), m_x(x), m_y(y), m_speed(0), m_moveTimer(0), m_width(width), m_height(height),
    m_health(3), m_life(true), m_isMove(false), m_name(name)
{
    m_texture.loadFromImage(image);
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_width / 2, m_height / 2);
}

Entity::~Entity() {

}

String Entity::getName()
{
    return m_name;
}

FloatRect Entity::getRect()
{
    return FloatRect(m_x, m_y, m_width, m_height);
}

float Entity::getSpeed()
{
    return m_speed;
}

int Entity::getHealth()
{
    return m_health;
}

bool Entity::isAlive()
{
    return m_life;
}

bool Entity::isMove()
{
    return m_isMove;
}

void Entity::setDemage(int amount)
{
    if(amount > m_health) {
        m_health = 0;
    }
    else {
        m_health -= amount;
    }
}

void Entity::setSpeed(float amount)
{
    m_speed = amount;
}
