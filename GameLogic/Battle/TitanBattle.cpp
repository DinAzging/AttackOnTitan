#include "TitanBattle.h"
#include "../../Entities/Player.h"
#include <iostream>
#include "../../Entities/Titan.h"

TitanBattle::TitanBattle(Player &player, Titan &titan, bool& buff) :
player(player), titan(titan), lastDiceResult(0), buff(buff) {}

TitanBattle::~TitanBattle()
{
}

void TitanBattle::startBattle()
{
    this->state = BattleState::Start;
}

int TitanBattle::playerAttack()
{
    this->lastDiceResult = this->player.diceRoll();

    if (this->lastDiceResult >= this->titan.getThrowDice())
    {
        this->titan.setHealth(this->titan.getHealth() - this->player.getDamage());
        this->state = BattleState::PlayerTurn;
    } 
    else
    {
        this->state = BattleState::TitanTurn;
    }

    if (this->titan.getHealth() == 0)
    {
        this->state = BattleState::PlayerWon;
        this->buff = false;
    }

    return lastDiceResult;
}

int TitanBattle::playerDefent()
{
    this->lastDiceResult = this->player.diceRoll();

    if (this->buff) ++this->lastDiceResult;

    if (this->lastDiceResult < this->titan.getThrowDice())
    {
        this->player.setHealth(this->player.getHealth() - this->titan.getDamage());
    }

    this->state = BattleState::PlayerTurn;

    if (this->player.getHealth() == 0)
    {
        this->state = BattleState::TitanWon;
    }

    if (this->buff) --this->lastDiceResult;
    
    return this->lastDiceResult;
}

bool TitanBattle::isBattleOver() const
{
    if ((this->state == BattleState::PlayerWon) || (this->state == BattleState::TitanWon))
    {
        this->buff = false;
        return true;
    }
    return false;
}

BattleState TitanBattle::getState() const
{
    return this->state;
}

BattleState &TitanBattle::getRefState()
{
    return this->state;
}
