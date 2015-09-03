#pragma once

#include "entity.h"

class Player : public Entity
{
public:
    Player(const Image &image, const String &name, Level &level, float x, float y, int width, int height);
    ~Player();
    void control();
    void checkCollisionsWithMap();
    void update(float time);

private:
    enum {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        SHOOT,
        STAY
    } m_state;
    int m_score;
};

