#ifndef STATE_DATA_H
#define STATE_DATA_H

#include <stack>
#include <map>
#include <string>

class State;
class GraphicsSettings;

namespace sf
{
    class RenderWindow;
}

class StateData
{
public:
    std::stack<State*>* states;
    GraphicsSettings* graphicsSettings;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;

    StateData();
    ~StateData();
};

#endif