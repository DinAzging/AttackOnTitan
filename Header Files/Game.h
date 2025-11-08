#ifndef GAME_H
#define GAME_H

#include <stack>
#include <map>
#include <string>
#include "../States/StateData.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "../Resource File/GraphicsSettings.h"
#include <SFML/Graphics/RenderWindow.hpp>

class State;

class Game
{
private:
    //Variables
    StateData stateData;
    GraphicsSettings graphicsSettings;
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    std::map <std::string, int> supportedKeys;

    //Initializer functions
    void initWindow();
    void initGraphicsSettings();
    void initKeys();
    void initStateData();
    void initStates();

public:
    //Constructors/Destructors
    Game();
    virtual ~Game();


    //Functions

    //Regular
    void endApplication();

    //Update
    void updateDt();
    void updateSFMLEvents();
    void update();
    
    //Render
    void render();
    void run();

};

#endif
