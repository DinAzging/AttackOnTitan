#include "../Header Files/Game.h"
#include "../States/State.h"
#include "../States/GameState.h"
#include <fstream>
#include <iostream>

// Initializer functions
void Game::initWindow()
{
    if (this->graphicsSettings.fullscreen)
    {
        this->window = new sf::RenderWindow
        (
            this->graphicsSettings.resolution,
            this->graphicsSettings.title,
            sf::Style::Fullscreen,
            this->graphicsSettings.contextSettings
        );
    }
    else
    {
        this->window = new sf::RenderWindow(
            this->graphicsSettings.resolution,
            this->graphicsSettings.title,
            sf::Style::Titlebar | sf::Style::Close, 
            this->graphicsSettings.contextSettings);
    }
    this->window->setFramerateLimit(this->graphicsSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->graphicsSettings.verticalSync);
}

void Game::initGraphicsSettings()
{
    this->graphicsSettings.loadFromFile("Config/graphics.txt");
}

void Game::initStateData()
{
    this->stateData.graphicsSettings = &this->graphicsSettings;
    this->stateData.window = this->window;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
}

void Game::initKeys()
{
    std::ifstream ifs("Config/supported_key.txt");
    
    if (ifs.is_open())
    {
        std::string key;
        int key_value = 0;

        while(ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
}

void Game::initStates()
{
    this->states.push(new GameState(&this->stateData));
}

// Constructors/Destructors
Game::Game()
{
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}


//Functions
void Game::endApplication()
{
    std::cout << "Ending Application" << "\n";
    this->window->close();
}

void Game::updateDt()
{
    /*Update the dt variable with time it takes to update render one frame*/
    this->dt = this->dtClock.restart().asSeconds();
    
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
        {
            this->endApplication();
        }
    }
}

void Game::update()
{
    this->updateSFMLEvents();

   if (!this->states.empty() /*&& this->window->hasFocus()*/)
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
           this->states.top()->endState();

            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->endApplication();
    }
    //Application End
}

void Game::render()
{
    this->window->clear();
  
    //Render items
    if (!this->states.empty())
    {
        this->states.top()->render();
    }

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
