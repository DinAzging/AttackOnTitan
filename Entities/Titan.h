#ifndef TITAN_H
#define TITAN_H

#include "Entity.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

enum TitanType : int {SLOW = 0, ORDINARY, ANOMALOUS};

class Titan : public Entity
{
private:
    TitanType titanType;
    unsigned short throwDice;

    sf::Text nameText;
    sf::Font font;
    sf::Font AoT_Font;

    void initVariables(int titan_type);
    void initTexture();
    void initFont();
    void initText();
    void initHealthLine();

public:
    Titan(int titan_type);
    //Titan(const Titan& other);
    virtual ~Titan();

    TitanType getType() const;
    unsigned short getThrowDice() const;

    void update(const float& dt);
    void render(sf::RenderTarget& target);
};


#endif // !TITAN_H