#ifndef MAP_H
#define MAP_H

#include "Cell.h"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Cell;

class Map
{
public:
    Map();
    virtual ~Map();
    
    sf::Vector2f getPositionHexagon(int indexX, float indexY);
    sf::Vector2i indexSearch(sf::Vector2f position);
    sf::Vector2i playerIndexSearch(sf::Vector2f playerPosition);

    template<typename Func>
    sf::Vector2i processRoute(std::string route, sf::Vector2f playerPosition, bool& out, Func action);

    sf::Vector2i ghostRoute(std::string route, sf::Vector2f playerPosition, bool& out);
    void deselectGhostRoute(std::string route, sf::Vector2f playerPosition, bool &out);

    void changeCell(sf::Vector2i playerPosition, Cell::CellType type);

    void selectCell(int index_x, int index_y);
    void deselectCell(int index_x, int index_y);

    Cell::CellType getCellType (sf::Vector2i index) const;
    sf::Vector2i getWorldSize() const;

    void update(const float& dt);
    void render(sf::RenderTarget&target);

private:
    std::vector< std::vector< Cell* > > map;

    sf::RectangleShape background;
    sf::Texture backgroundTexture;

    sf::Color gostColor;

    size_t worldSizeWidth;
    size_t worldSizeHeight;

    void clear();

    char getRandomCell();
    
    void initVariables();

    void initMap();
    void initBackground();
};


#endif

