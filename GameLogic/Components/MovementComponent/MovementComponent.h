#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

//#include "../Map/Map.h"
//#include "../Entities/Player.h"
//#include "../GUI/PlayerCard.h"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "../../../Map/Cell.h"

class Player;
class Map;


namespace gui
{
    class PlayerCard;
    class Deck;
}


class MovementComponent 
{
private:
    Map& map;
    Player& player;
    std::vector<gui::PlayerCard*>& playerHand;
    gui::Deck& deck;
    gui::Deck& discard;
    
    sf::FloatRect playerHandBounds;

    bool choice;
    bool out;
    bool doubleMove;
    bool react;

public:
    MovementComponent(Map& map, Player& player, std::vector<gui::PlayerCard*>& hand, gui::Deck& deck, gui::Deck& discard);
    ~MovementComponent();

    void handleFirstStage(sf::Vector2i mouse_pos, bool keytime);
    void handleCardSelection(int card_index, sf::Vector2i mouse_pos, bool keytime);
    void handleSpecialCard(int card_index, sf::Vector2i mouse_pos, bool keytime, char card_type);
    void handleMovementCard(int card_index, char card_type);
    void handleResponseKey();
    void changeCard(int card_index, const sf::Vector2i& index);

    void confirmMovement();

    Cell::CellType getCellTypeForCard(char card_type) const;

    void lockAllCards();
    void unlockAllCards();

    void resetCardSelection(int card_index);
    
    bool shouldReact() const;
    void setReact(bool react);
};
#endif