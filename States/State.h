#ifndef STATE_H
#define STATE_H

#include <stack>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class StateData;
class GraphicsSettings;

class State
{
public:
    //Constructors/Destructors
    State(StateData* state_data);
    virtual ~State();

    //Functions

    const bool& getQuit() const;

    virtual void checkForQuit();
    virtual void endState() = 0;

    void updateMousePositions(sf::View* view);
    virtual void updateKeybinds(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
    //Variables
    StateData* stateData;
    std::stack<State*>* states;
    sf::RenderWindow* window;
    GraphicsSettings* graphicsSettings;
    std::vector<sf::Texture> texture;
    sf::Font font;

    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosView;
    sf::Vector2i mousePosIndex;

    std::map <std::string, int>* supportedKeys;
    std::map <std::string, int> keybinds;

    //Initializer functions
};
#endif
