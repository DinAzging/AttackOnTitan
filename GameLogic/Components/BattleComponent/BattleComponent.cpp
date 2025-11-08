#include "BattleComponent.h"
#include "../../../Resource File/Gui.h"
#include "../../../Entities/Titan.h"
#include "../../../Entities/Player.h"
#include "../../Battle/TitanBattle.h"
#include "../../../Map/Map.h"
#include <random>
#include <iostream>

BattleComponent::BattleComponent(Player &player, Map& map) 
    : battleActive(false), player(player), map(map)
{
    this->diceResult = "";
    this->diceButtonPressed = false;
}

BattleComponent::~BattleComponent()
{
}

void BattleComponent::startBattle(bool& buff) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(1, 3);
    
    this->titan = std::make_unique<Titan>(distribution(gen));

    this->buff = buff;
    this->battleActive = true;

    this->currentBattle = std::make_unique<TitanBattle>(this->player, *titan, buff);
    this->battleWindow = std::make_unique<gui::BattleWindow>
    (
        sf::Vector2f(460.f, 130.f), sf::Vector2f(1005.f, 680.f), 
        this->player, *this->titan, this->currentBattle->getRefState()
    );

    this->currentBattle->startBattle();
}

bool BattleComponent::isBattleActive() const
{
    return this->battleActive;
}

void BattleComponent::endBattle()
{
    this->currentBattle.reset();
    this->titan.reset();
    this->battleWindow.reset();
    this->battleActive = false;
}

void BattleComponent::update(gui::Button& dice_button, const float &dt, const sf::Vector2i &mouse_pos_window)
{
    if (!this->currentBattle) return;

    if (this->diceButtonPressed)
    {
        this->diceButtonPressed = false;
    }

    bool should_unlock = 
    !(
        this->currentBattle->getState() == PlayerTurn || 
        this->currentBattle->getState() == TitanTurn
    );

    dice_button.setLock(should_unlock);

    if (dice_button.isReleased()) 
    {
        this->diceButtonPressed = true;

        if (this->currentBattle->getState() == PlayerTurn) 
        {
            this->diceResult = std::to_string(currentBattle->playerAttack());
        } 

        else if (this->currentBattle->getState() == TitanTurn) 
        {            
            if (this->buff) 
            {
                this->diceResult = std::to_string(currentBattle->playerDefent()) + " + 1"; 
            }
            else
            {
                this->diceResult = std::to_string(currentBattle->playerDefent());
            }
        }
    }

    if (this->currentBattle->getRefState() == PlayerWon)
    {
        this->map.changeCell(this->map.playerIndexSearch(this->player.getPosition()), Cell::CellType::DeadTitan);
    }

    if (this->battleWindow)
    {
        if (this->battleWindow->isShowWindow())
        {
            if (this->currentBattle->getState() == Start) 
            {               
                this->battleWindow->update(dt, mouse_pos_window);
            }

            else
            {
                this->battleWindow->update(dt, mouse_pos_window, this->diceResult, this->diceButtonPressed);
            }
        }
    }

    if (!this->battleWindow->isShowWindow()) 
    {
        this->endBattle();
    }
}

void BattleComponent::render(sf::RenderTarget *target)
{
    if (this->battleWindow)
    {
        if (this->battleWindow->isShowWindow())
        {
            this->battleWindow->render(target);
        }
    }
}