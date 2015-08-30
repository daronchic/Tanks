#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TinyXML/tinyxml.h"

struct Object
{
    int getPropertyInt(std::string name);
    float getPropertyFloat(std::string name);
    std::string getPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<float> rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

class Level
{
public:
    bool loadFromFile(std::string filename);
    Object getObject(std::string name);
    std::vector<Object> getObjects(std::string name);
    std::vector<Object> getAllObjects();
    void draw(sf::RenderWindow &window);
    sf::Vector2i getTileSize();

private:
    int m_width, m_height, m_tileWidth, m_tileHeight;
    int m_firstTileID;
    sf::Rect<float> m_drawingBounds;
    sf::Texture m_tilesetImage;
    std::vector<Object> m_objects;
    std::vector<Layer> m_layers;
};
