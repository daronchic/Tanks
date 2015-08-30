#include "level.h"

int Object::getPropertyInt(std::string name)
{
    return atoi(properties[name].c_str());
}

float Object::getPropertyFloat(std::string name)
{
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::getPropertyString(std::string name)
{
    return properties[name];
}

bool Level::loadFromFile(std::string filename)
{
    TiXmlDocument levelFile(filename.c_str());

    if (!levelFile.LoadFile()) {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    m_width = atoi(map->Attribute("width"));
    m_height = atoi(map->Attribute("height"));
    m_tileWidth = atoi(map->Attribute("tilewidth"));
    m_tileHeight = atoi(map->Attribute("tileheight"));

    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    m_firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    sf::Image img;

    if (!img.loadFromFile(imagepath))
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }


    img.createMaskFromColor(sf::Color(255, 255, 255));
    m_tilesetImage.loadFromImage(img);
    m_tilesetImage.setSmooth(false);

    int columns = m_tilesetImage.getSize().x / m_tileWidth;
    int rows = m_tilesetImage.getSize().y / m_tileHeight;

    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++) {
            sf::Rect<int> rect;

            rect.top = y * m_tileHeight;
            rect.height = m_tileHeight;
            rect.left = x * m_tileWidth;
            rect.width = m_tileWidth;

            subRects.push_back(rect);
        }

    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;

        if (layerElement->Attribute("opacity") != NULL)	{
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        }
        else {
            layer.opacity = 255;
        }

        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if(layerDataElement == NULL) {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL) {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement)	{
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - m_firstTileID;

            if (subRectToUse >= 0)
            {
                sf::Sprite sprite;
                sprite.setTexture(m_tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * m_tileWidth, y * m_tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= m_width)
            {
                x = 0;
                y++;
                if (y >= m_height)
                    y = 0;
            }
        }

        m_layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    TiXmlElement *objectGroupElement;

    if (map->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement)
            {
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(m_tilesetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != NULL) {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                }
                else {
                    width = subRects[atoi(objectElement->Attribute("gid")) - m_firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - m_firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - m_firstTileID]);
                }

                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::Rect <float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL) {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }


                m_objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

Object Level::getObject(std::string name)
{
    for (int i = 0; i < m_objects.size(); i++)
        if (m_objects[i].name == name)
            return m_objects[i];
}

std::vector<Object> Level::getObjects(std::string name)
{
    std::vector<Object> vec;
    for (int i = 0; i < m_objects.size(); i++)
        if (m_objects[i].name == name)
            vec.push_back(m_objects[i]);

    return vec;
}


std::vector<Object> Level::getAllObjects()
{
    return m_objects;
}


sf::Vector2i Level::getTileSize()
{
    return sf::Vector2i(m_tileWidth, m_tileHeight);
}

void Level::draw(sf::RenderWindow &window)
{
    for (int layer = 0; layer < m_layers.size(); layer++)
        for (int tile = 0; tile < m_layers[layer].tiles.size(); tile++)
            window.draw(m_layers[layer].tiles[tile]);
}
