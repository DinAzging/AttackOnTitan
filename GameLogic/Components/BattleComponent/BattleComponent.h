#ifndef BATTLE_COMPONENT_H
#define BATTLE_COMPONENT_H

//#include "../Entities/Player.h"
//#include "../Entities/Titan.h"
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

class Player;
class Map;
class Titan;
class TitanBattle;

namespace gui
{
    class Button;
    class BattleWindow;
}

class BattleComponent
{
private:
    std::unique_ptr<TitanBattle> currentBattle;
    std::unique_ptr<Titan> titan;
    std::unique_ptr<gui::BattleWindow> battleWindow;

    Player& player;
    Map& map;

    std::string diceResult;
    
    bool battleActive;

    bool diceButtonPressed;

    bool buff;

public:
    BattleComponent(Player &player, Map& map);
    ~BattleComponent();

    void startBattle(bool& buff);
    bool isBattleActive() const;
    void endBattle();

    void update(gui::Button& dice_button, const float &dt, const sf::Vector2i &mouse_pos_window);
    void render(sf::RenderTarget* target);
    

};
#endif