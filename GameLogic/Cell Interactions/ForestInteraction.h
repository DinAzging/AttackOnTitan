#ifndef FOREST_INTERACTION_H
#define FOREST_INTERACTION_H

#include <vector>
#include <SFML/System/Vector2.hpp>

class Map;

class ForestInteraction
{
private:
    const Map& map;
    std::vector<sf::Vector2i> localTitanIndex;

    void printVector();

public:
    ForestInteraction(const Map& map);
    ~ForestInteraction();

    void checkTitan(int index_x, int index_y);
    const std::vector<sf::Vector2i>& getTitanIndex() const;

    void update(const sf::Vector2i &player_position);
};

#endif 