#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include <memory>
#include <vector>
#include "SFML/Graphics/RenderTarget.hpp"
#include "../Resource File/Gui.h"

class StateData;
class Map;
class Player;

class MovementComponent;
class BattleComponent;
class ViewComponent;
class WarehouseComponent;
class ForestComponent;
class BeastThrowComponent;


class GameState : public State
{
public:
    //Constructors/Destructors
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void endState();

    const bool getKeytime();

    bool isPlayerOnTitanCell() const;
    bool isPlayerOnBeastCell() const;
    bool isPlayerOnForestCell() const;
    bool isPlayerOnWarehouseCell() const;

    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

private:
    //Variables
    std::unique_ptr<Map> map;
    std::unique_ptr<Player> player;

    std::unique_ptr<BattleComponent> battleComponent;
    std::unique_ptr<MovementComponent> movementComponent;
    std::unique_ptr<ViewComponent> viewComponent;
    std::unique_ptr<WarehouseComponent> warehouseComponent;
    std::unique_ptr<ForestComponent> forestComponent;
    std::unique_ptr<BeastThrowComponent> beastThrowComponent;

    gui::Deck deck;
    gui::Deck discard;

    std::vector<gui::PlayerCard*> playerHand;

    std::unique_ptr<gui::PlayerWindow> playerWindow;

    std::map <std::string, gui::Button*> buttons;
    
    sf::View view;
    sf::View defaultView;

    sf::Font AoT_Font;
    sf::Font font;

    sf::Text stage;
    sf::Text diceResult;

    sf::RectangleShape background;

    std::vector <std::unique_ptr <gui::WarehouseCard> > warehouseCard;

    unsigned short int maxCard;

    float keytime;
    float keytimeMax;

    bool buff;

    //Initializer functions
    void initVariables();
    void initKeybinds();
    void initView();
    void initMap();
    void initPlayer();
    void initPlayerCards();
    void initButtons();
    void initFont();
    void initPlayerWindow();
    void initComponents();

    void deletePlayerCards();
    void deleteButtons();

    void handleSecondStage();

    void updateKeyTime(const float& dt);
    void updateMousePosIndex();
    void updateGui(const float& dt, const sf::Vector2i& mouse_pos_window);
    void updatePlayerWindow(const float& dt, const sf::Vector2i& mouse_pos_window);
    void updateKeybinds(const float& dt);
    void updateTitanButton();
    void updateWarehouseButton();
    void updateForest();
    void updateBeast(const float& dt);

    void renderGui(sf::RenderTarget& target);
};
#endif // !GAMESTATE_H