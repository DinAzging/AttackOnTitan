#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace sf
{
    class RenderTarget;
};

class Entity
{
public:
    Entity();
    ~Entity();

    virtual unsigned short getHealth();
    virtual unsigned short getDamage(); // хзхз

    virtual void setHealth(unsigned short health);
    virtual void setDamage(unsigned short damage);

    virtual void setPositionHealthLine(sf::Vector2f position);
    virtual sf::Vector2f getPositionHealthLine();

    virtual std::vector<sf::RectangleShape>& getHealthLine();
    
    virtual std::string getName();

    virtual void update(const float& dt) = 0; 
    virtual void renderHealthLine(sf::RenderTarget& target);

protected:
    sf::Sprite sprite;

    std::string name;
    
    sf::RectangleShape healthBox;
    sf::Texture healthTexture;
    
    std::vector<sf::RectangleShape> healthLine;

    virtual void initHealthLine() = 0;

    unsigned short health;
    unsigned short damage;

};
#endif 