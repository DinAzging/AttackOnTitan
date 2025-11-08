#include "ForestComponent.h"
#include "../../Cell Interactions/ForestInteraction.h"
#include "../../../Resource File/Gui.h"
#include "../../../Map/Map.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

ForestComponent::ForestComponent(Map &map)
    : map(map), buff(false), fight(false)
{
    this->forestInteraction = std::make_unique <ForestInteraction>(this->map);
}

ForestComponent::~ForestComponent()
{
}

bool& ForestComponent::getBuff()
{
    return this->buff;
}

bool ForestComponent::getFight() const
{
    return this->fight;
}

void ForestComponent::update(const sf::Vector2i &mouse_pos_index, gui::Button& titan_button, bool keytime, const sf::Vector2i &player_position)
{
    this->forestInteraction->update(player_position);

    this->titanIndex = this->forestInteraction->getTitanIndex();

    if (!this->titanIndex.empty())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && keytime)
        {
            for (size_t i = 0; i < this->titanIndex.size(); i++)
            {
                if (mouse_pos_index == this->titanIndex[i])
                {
                    this->map.selectCell(this->titanIndex[i].x, this->titanIndex[i].y);
                    titan_button.setLock(false);
                    this->buff = true;
                    this->fight = true;
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && keytime)
        {
            for (size_t i = 0; i < this->titanIndex.size(); i++)
            {
                if (mouse_pos_index == this->titanIndex[i])
                {
                    this->map.deselectCell(this->titanIndex[i].x, this->titanIndex[i].y);
                    titan_button.setLock(true);
                    this->buff = false;
                    this->fight = false;
                }
            }
        }
    }
}
