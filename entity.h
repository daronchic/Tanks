#pragma once

#include "level.h"

#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

class Entity
{
public:
    Entity(const Image &image, const String &name, float x, float y, int width, int height);
    ~Entity();
    FloatRect getRect();
    String getName();
    float getSpeed();
    int getHealth();
    bool isAlive();
    bool isMove();
    void setDemage(int amount);
    void setSpeed(float amount);

    virtual void update(float time) = 0;
    virtual void checkCollisionsWithMap() = 0;

    std::vector<Object> m_object;

protected:
    float m_directionX, m_directionY, m_x, m_y, m_speed, m_moveTimer;
    int m_width, m_height, m_health;
    bool m_life, m_isMove;
    Texture m_texture;
    Sprite m_sprite;
    String m_name;

};

