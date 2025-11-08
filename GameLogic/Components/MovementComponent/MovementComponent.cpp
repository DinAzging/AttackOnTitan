#include "MovementComponent.h"
#include "../../../Resource File/Gui.h"
#include "../../../Map/Map.h"
#include "../../../Entities/Player.h"
#include <iostream>

MovementComponent::MovementComponent(Map &map, Player &player, std::vector<gui::PlayerCard *> &hand, gui::Deck &deck, gui::Deck &discard)
    : map(map), player(player), playerHand(hand), 
      deck(deck), discard(discard), 
      choice(true), out(false), doubleMove(false), react(false)
{
    this->playerHandBounds.left = hand[0]->getPosition().x;
    this->playerHandBounds.width = hand[hand.size() - 1]->getPosition().x + hand[hand.size() - 1]->getSize().x - hand[0]->getPosition().x;
    this->playerHandBounds.top = hand[0]->getPosition().y;
    this->playerHandBounds.height = hand[0]->getPosition().y + hand[0]->getSize().y;
}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::handleFirstStage(sf::Vector2i mouse_pos, bool keytime)
{
    if (!this->react)
    for (int i = 0; i < this->playerHand.size(); ++i) 
    {
        if (this->playerHand[i]->isHover() && !this->playerHand[i]->getGost() && this->choice) 
        {
            this->handleCardSelection(i, mouse_pos, keytime);
            break;
        }

        if (!this->playerHand[i]->isHover() && this->playerHand[i]->getGost()) 
        {
            resetCardSelection(i);
            break;
        }
    }
}

void MovementComponent::handleCardSelection(int card_index, sf::Vector2i mouse_pos, bool keytime)
{
    char card_type = this->playerHand[card_index]->getRoute()[0];
    
    if (card_type == 'f' || card_type == 't' || card_type == 'w' || card_type == 'b') 
    {
        this->handleSpecialCard(card_index, mouse_pos, keytime, card_type);
    } 
    else 
    {
        handleMovementCard(card_index, card_type);
    }
}

void MovementComponent::handleSpecialCard(int card_index, sf::Vector2i mouse_pos, bool keytime, char card_type)
{
    if (keytime && sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        //if(!this->playerHandBounds.contains(static_cast<sf::Vector2f>(mouse_pos)))
        //{
            this->lockAllCards();
        
            sf::Vector2i new_index = this->map.indexSearch(sf::Vector2f(mouse_pos.x, mouse_pos.y));
            Cell::CellType required_type = this->getCellTypeForCard(card_type);
            
            if (this->map.getCellType(new_index) == required_type) 
            {
                this->changeCard(card_index, new_index);
                this->react = true;
            }
        //}
    }
}

void MovementComponent::handleMovementCard(int card_index, char card_type)
{
    this->unlockAllCards();
    this->doubleMove = (card_type == 'd');
    
    this->player.newIndex = this->map.ghostRoute(this->playerHand[card_index]->getRoute(), this->player.getPosition(), this->out);
    
    if (!this->out) 
    {
        this->playerHand[card_index]->setGost(true);
        this->lockAllCards();
        this->choice = false;
    } 
    else 
    {
        this->map.deselectGhostRoute(playerHand[card_index]->getRoute(), player.getPosition(), out);
        this->out = false;
        this->playerHand[card_index]->dontHover();
    }
}

void MovementComponent::handleResponseKey()
{
    if (this->react)
    {
        this->react = false;
    }
}

void MovementComponent::changeCard(int card_index, const sf::Vector2i &index)
{
    this->playerHand[card_index]->dontHover();
    this->playerHand[card_index]->setGost(false);

    this->discard.addCard(*playerHand[card_index]);

    if (this->deck.isEmpty()) 
    {
        this->discard.shuffle();
        this->deck = discard;
        this->discard.clear();
    }
    
    delete this->playerHand[card_index];

    this->playerHand[card_index] = new gui::PlayerCard(deck.distribution());
    this->playerHand[card_index]->setPosition(5.f + 475.0f + 90.f + card_index * 160.f, 810.0f);

    this->player.setPosition(this->map.getPositionHexagon(index.x, index.y));
    this->unlockAllCards();
    this->choice = true;
}

void MovementComponent::resetCardSelection(int card_index)
{
    this->playerHand[card_index]->setGost(false);

    this->map.deselectGhostRoute(playerHand[card_index]->getRoute(), this->player.getPosition(), out);

    this->unlockAllCards();
    this->choice = true;
}

void MovementComponent::confirmMovement()
{
    for (int i = 0; i < this->playerHand.size(); i++) 
    {
        if (this->playerHand[i]->getGost()) 
        {
            this->map.deselectGhostRoute(this->playerHand[i]->getRoute(), this->player.getPosition(), out);
            this->changeCard(i, this->player.newIndex);
            this->choice = true;
            
            if (!this->doubleMove) 
            {
                this->react = true;
            }
        }
    }
}

Cell::CellType MovementComponent::getCellTypeForCard(char card_type) const
{
    switch (card_type) 
    {
        case 'f': return Cell::CellType::Forest;

        case 't': return Cell::CellType::Titan;

        case 'w': return Cell::CellType::Warehouse;

        case 'b': return Cell::CellType::Beast;

        default: return Cell::CellType::Idle;
    }
}

void MovementComponent::lockAllCards()
{
    for (auto& card : this->playerHand) 
    {
        card->cantPress();
    }
}

void MovementComponent::unlockAllCards()
{
    for (auto& card : this->playerHand) 
    {
        card->canPress();
    }
}

bool MovementComponent::shouldReact() const
{
    return this->react;
}

void MovementComponent::setReact(bool react)
{
    this->react = react;
}
