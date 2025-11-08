#ifndef FOREST_COMPONENT_H
#define FOREST_COMPONENT_H

#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>

class Map;
class ForestInteraction;

namespace gui
{
    class Button;
}

class ForestComponent
{
private:
    Map& map;
    std::vector<sf::Vector2i> titanIndex;
    std::unique_ptr<ForestInteraction> forestInteraction;

    bool buff;
    bool fight;

public:
    ForestComponent(Map& map);
    ~ForestComponent();

    bool& getBuff();
    bool getFight() const;

    void update(const sf::Vector2i& mouse_pos_index, gui::Button& titan_button, bool keytime, const sf::Vector2i &player_position);
};
#endif 