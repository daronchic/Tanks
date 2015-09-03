#pragma once

#include <SFML/Graphics.hpp>

sf::View playerView;

void setPlayerCoordinatesForView(float x, float y) {
    playerView.setCenter(x, y);
}
