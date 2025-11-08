#include "Entity.h"
#include "SFML/Graphics/RenderTarget.hpp"

Entity::Entity()
{

} 

Entity::~Entity()
{
    
}

unsigned short Entity::getHealth()
{
    return this->health;
}

unsigned short Entity::getDamage()
{
    return this->damage;
}

void Entity::setHealth(unsigned short health)
{
    this->health = health;
}

void Entity::setDamage(unsigned short damage)
{
    this->damage = damage;
}

void Entity::setPositionHealthLine(sf::Vector2f position)
{
    if(!this->healthLine.empty())
    {    
        for(size_t i = 0; i < this->getHealth(); i++)
        {
            this->healthLine[i].setPosition
            (
                position.x + (i * 50), position.y
            );
        }
    }
}

sf::Vector2f Entity::getPositionHealthLine()
{
    return sf::Vector2f
    (
        this->healthLine[0].getPosition().x,
        this->healthLine[0].getPosition().y
    );
}

std::vector<sf::RectangleShape>& Entity::getHealthLine()
{
    return this->healthLine;
}

std::string Entity::getName()
{
    return this->name;
}

void Entity::renderHealthLine(sf::RenderTarget &target)
{
    if(!this->healthLine.empty())
    {
        for(int i = 0; i < this->getHealth(); i++)
        {
            target.draw(this->healthLine[i]);
        }
    }
}
