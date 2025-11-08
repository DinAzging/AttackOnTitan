#include "Player.h"
#include <random>
#include <ctime>

void Player::initInfoString()
{
    if (this->name == "Eren Yeager")
    {
        this->description = "You can become a titan three times per game. Now you can attack the titans from adjacent cells and carry out an attack twice in a row. The effect ends when you lose your life token";
    }
}

void Player::initVariables()
{
    this->dot.setRadius(24.0f);
    this->dot.setFillColor(sf::Color::White);
}

void Player::initTexture()
{
    if(!this->healthTexture.loadFromFile("Resources/Picture/heart.png"))
    {
        exit(1);
    }
}

void Player::initHealthLine()
{
    this->healthBox.setSize(sf::Vector2f(50.f, 50.f));
    this->healthBox.setTexture(&this->healthTexture);

    for (int i = 0; i < this->getHealth(); i++)
    {
        this->healthLine.push_back(healthBox);
    }

    this->setPositionHealthLine(sf::Vector2f(190, 20));
}

Player::Player(sf::Vector2f position, std::string name) : Entity(), broken(false)
{
    this->setHealth(4);
    this->setDamage(1); 
    this->name = name;

    this->initVariables();
    this->initTexture();
    this->initHealthLine();
    

    this->setPosition(sf::Vector2f(position.x, position.y));
}

Player::~Player()
{
}

sf::Vector2f Player::getPosition()
{
    return this->dot.getPosition();
}

std::string Player::getDescription()
{
    return this->description;
}

void Player::setPosition(sf::Vector2f position)
{
    this->dot.setPosition(position.x + 26.0f, position.y + 26.0f);
}

int Player::diceRoll()
{
    srand(time(0));
    
    return rand()%(6 - 1 + 1) + 1;
}

void Player::update(const float& dt)
{
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->dot);
}