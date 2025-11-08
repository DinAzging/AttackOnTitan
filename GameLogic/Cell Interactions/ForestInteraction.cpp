#include "ForestInteraction.h"
#include "../../Map/Map.h"
#include "../../Resource File/Gui.h"
#include<iostream>

void ForestInteraction::printVector()
{
    std::cout<<std::endl<<std::endl;

    if (!this->localTitanIndex.empty())
    {    
        std::cout<<"Titan indexes:"<<std::endl;

        for (int i = 0; i < this->localTitanIndex.size(); i++)
        {
            std::cout<< "x: " << this->localTitanIndex[i].x << "  y: " << this->localTitanIndex[i].y<<std::endl;
        }
    }
    else
    {
        std::cout<<"Null"<<std::endl;
    }
}

ForestInteraction::ForestInteraction(const Map &map)
    : map(map)
{}

ForestInteraction::~ForestInteraction()
{
}

void ForestInteraction::checkTitan(int index_x, int index_y)
{
    if (this->map.getCellType(sf::Vector2i(index_x, index_y)) == Cell::CellType::Titan)
    {
        sf::Vector2i newTitan(index_x, index_y);

        if (std::find(localTitanIndex.begin(), localTitanIndex.end(), newTitan) == localTitanIndex.end())
        {
            this->localTitanIndex.push_back(newTitan);
        }
    }
}

const std::vector<sf::Vector2i> &ForestInteraction::getTitanIndex() const
{
    return this->localTitanIndex;
}

void ForestInteraction::update(const sf::Vector2i &player_position)
{
    this->localTitanIndex.clear();

    for (int i = player_position.y - 2, it = 1; i <= player_position.y + 2; i++, it++)
    {
        if (i < 0 || i >= this->map.getWorldSize().y) continue;
        else
        {
            if (it == 1 || it == 5)
            {   
                for (int j = player_position.x - 1; j <= player_position.x + 1; j++)
                {
                    if (j < 0 || j >= this->map.getWorldSize().x) continue;
                    else
                    {
                        this->checkTitan(j,i);
                    }
                }
                continue;
            }
        
            if (it == 3)
            {
                for (int j = player_position.x - 2; j <= player_position.x + 2; j++)
                {
                    if (j < 0 || j >= this->map.getWorldSize().x) continue;
                    else
                    {
                        this->checkTitan(j,i);
                    }
                }
                continue;
            }
        
            else
            {
                if (i % 2 != 0)
                {
                    for (int j = player_position.x - 1; j <= player_position.x + 2; j++)
                    {
                        if (j < 0 || j >= this->map.getWorldSize().x) continue;
                        else
                        {
                            this->checkTitan(j,i);
                        }
                    }
                    continue;
                }
            
                else
                {
                    for (int j = player_position.x - 2; j <= player_position.x + 1; j++)
                    {
                        if (j < 0 || j >= this->map.getWorldSize().x) continue;
                        else
                        {
                            this->checkTitan(j,i);
                        }
                    }
                    continue;
                }
            }
        }
    }
}
