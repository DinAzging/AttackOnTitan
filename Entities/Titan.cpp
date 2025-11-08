#include "Titan.h"

void Titan::initVariables(int titan_type)
{
    switch (titan_type)
    {
    case 1:
        this->setHealth(1);
        this->setDamage(1);
        this->throwDice = 3; 
        this->name = "Slow Titan";
        this->titanType = TitanType::SLOW;

        break;

    case 2:
        this->setHealth(2);
        this->setDamage(1);
        this->throwDice = 4; 
        this->name = "Ordinary Titan";
        this->titanType = TitanType::ORDINARY;
       
        break;

    case 3:
        this->setHealth(3);
        this->setDamage(1);
        this->throwDice = 5; 
        this->name = "Anomalous Titan";
        this->titanType = TitanType::ANOMALOUS;

        break;
    
    default:
        break;
    }
}

void Titan::initTexture()
{
    if(!this->healthTexture.loadFromFile("Resources/Picture/heart.png"))
    {
        exit(1);
    }
}

void Titan::initFont()
{
	if (!this->font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
	{
		exit(1);
	}

    if (!this->AoT_Font.loadFromFile("Resources/Fonts/AoT_Font.ttf"))
	{
    	exit(1);
    }
}

void Titan::initText()
{
    this->nameText.setString(this->name);
    this->nameText.setFont(AoT_Font);
    this->nameText.setCharacterSize(70);
    this->nameText.setPosition(1150.f, 5.f);
}

void Titan::initHealthLine()
{
    this->healthBox.setSize(sf::Vector2f(50.f, 50.f));
    this->healthBox.setTexture(&this->healthTexture);

    for (int i = 0; i < this->getHealth(); i++)
    {
        this->healthLine.push_back(healthBox);
    }

    this->setPositionHealthLine(sf::Vector2f(this->nameText.getPosition().x + this->nameText.getGlobalBounds().width + 50.f, 20.f));
}


Titan::Titan(int titan_type) : Entity()
{
    initVariables(titan_type);
    initTexture();
    initFont();
    initText();
    initHealthLine();
}

// Titan::Titan(const Titan &other)
// {
//     this->AoT_Font = other.AoT_Font;
//     this->damage = other.damage;
//     this->font = other.font;
//     this->health = other.health;
//     this->healthBox = other.healthBox;
//     this->healthLine = other.healthLine;
//     this->healthTexture = other.healthTexture;
//     this->sprite = other.sprite;
//     this->throwDice = other.throwDice;
//     this->titanName = other.titanName;
//     this->titanNameText = other.titanNameText;
//     this->titanType = other.titanType;
// }

Titan::~Titan()
{

}

TitanType Titan::getType() const
{
    return this->titanType;
}

unsigned short Titan::getThrowDice() const
{
    return this->throwDice;
}

void Titan::update(const float &dt)
{

}

void Titan::render(sf::RenderTarget& target)
{
    target.draw(this->nameText);

    this->renderHealthLine(target);
}


