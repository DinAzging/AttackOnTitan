#ifndef TITANBATTLE_H
#define TITANBATTLE_H

class Player;
class Titan;

enum BattleState : int
{
    Start = 0,
    PlayerTurn,    
    TitanTurn,     
    PlayerWon,
    TitanWon
};

class TitanBattle
{
private:
    Player& player;
    Titan& titan;
    BattleState state;
    int lastDiceResult;

    bool& buff;
    
public:
    TitanBattle(Player& player, Titan& titan, bool& buff);
    ~TitanBattle();

    void startBattle();
    int playerAttack();
    int playerDefent();
    bool isBattleOver() const;
    BattleState getState() const;

    BattleState& getRefState();
};

#endif