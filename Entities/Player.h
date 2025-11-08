#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Player : public Entity
{
public:
    Player(sf::Vector2f position, std::string name);
    ~Player();

    sf::Vector2i index;    //вынести в
    sf::Vector2i newIndex; //privat

    std::string description;
    
    sf::Vector2f getPosition();
    std::string getDescription();

    void setPosition(sf::Vector2f position);

    int diceRoll();

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);

private:
    sf::CircleShape dot;

    sf::RectangleShape brokenHealthBox;
    sf::Texture brokenHealthTexture;

    bool broken;

    void initInfoString();
    void initVariables();
    void initTexture();
    void initHealthLine();
    
};
#endif 