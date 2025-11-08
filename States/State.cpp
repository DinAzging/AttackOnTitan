#include "State.h"
#include "StateData.h"
//Constructors/Destructors

State::State(StateData* state_data)
{
    this->stateData = state_data;
    this->states = state_data->states;
    this->graphicsSettings = state_data->graphicsSettings;
    this->window = state_data->window;
    this->supportedKeys = state_data->supportedKeys;
    this->quit = false;
}
State::~State()
{

}

const bool &State::getQuit() const
{
    return this->quit;
}

// Functions
void State::updateMousePositions(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    if (view)
    {
        this->window->setView(*view);
    }

    this->mousePosView = sf::Vector2i
    (
        static_cast<int>(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)).x),
        static_cast<int>(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)).y)
    );

    this->window->setView(this->window->getDefaultView());
}

void State::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->quit = true;
    }
}

