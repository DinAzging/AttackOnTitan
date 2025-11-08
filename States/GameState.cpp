#include "GameState.h"
#include "StateData.h"
#include "../Map/Map.h"
#include "../Entities/Player.h"
#include "../Resource File/GraphicsSettings.h"

#include "../GameLogic/Components/BattleComponent/BattleComponent.h"
#include "../GameLogic/Components/MovementComponent/MovementComponent.h"
#include "../GameLogic/Components/ViewComponent/ViewComponent.h"
#include "../GameLogic/Components/WarehouseComponent/WarehouseComponent.h"
#include "../GameLogic/Components/ForestComponent/ForestComponent.h"
#include "../GameLogic/Components/BeastThrowComponent/BeastThrowComponent.h"

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <sstream>
#include <fstream>


void GameState::initVariables()
{
    this->background.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

    this->background.setFillColor(sf::Color(205, 133, 63));

    this->maxCard = 5;

    this->warehouseCard = std::vector<std::unique_ptr<gui::WarehouseCard>>();
}

void GameState::initKeybinds()
{
    std::ifstream ifs("Config/keybinds.txt");

	if (ifs.is_open())
	{
		std::string key1 = "";
		std::string key2 = "";

		while (ifs >> key1 >> key2)
		{
			this->keybinds[key1] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void GameState::initView()
{
    this->view.setSize
    (
        this->stateData->graphicsSettings->resolution.width,
        this->stateData->graphicsSettings->resolution.height
    );

    this->view.setCenter
    (
        sf::Vector2f
        (
            this->stateData->graphicsSettings->resolution.width / 2,
            this->stateData->graphicsSettings->resolution.height / 2
        )
    );

    this->defaultView = this->view;
}

void GameState::initMap()
{
    this->map = std::make_unique<Map>();
}

void GameState::initPlayer()
{
    this->player = std::make_unique<Player>(this->map->getPositionHexagon(0,0), "Eren Yeager");
}

void GameState::initPlayerCards()
{
    for (int i = 0; i < this->maxCard; ++i) 
    {
        gui::PlayerCard* card = new gui::PlayerCard(deck.distribution());
        playerHand.push_back(card);
        playerHand[i]->setPosition(5.f + 475.0f + 90.f + i * 160.f, 810.0f);
    }
}

void GameState::initButtons()
{
    this->buttons["DICE_BTN"] = new gui::Button
    (
        1920.f - 74.f - 3.f, 90.f, 74.f, 74.f,
        &this->AoT_Font, "D", 30, true,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );

    this->buttons["TITAN_BTN"] = new gui::Button
    (
        1920.f - 74.f - 3.f, 170.f, 74.f, 74.f,
        &this->AoT_Font, "T", 30, true,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );

    this->buttons["WAREHOUSE_BTN"] = new gui::Button
    (
        1920.f - 74.f - 3.f, 250.f, 74.f, 74.f,
        &this->AoT_Font, "W", 30, true,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );
}

void GameState::initFont()
{
	if (!this->font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
	{
		exit(1);
	}

    if (!this->AoT_Font.loadFromFile("Resources/Fonts/AoT_Font.ttf"))
	{
    	exit(1);
    }
}

void GameState::initComponents()
{
    this->battleComponent = std::make_unique<BattleComponent>(*this->player, *this->map);

    this->movementComponent = std::make_unique<MovementComponent>(*map, *player, playerHand, deck, discard);

    this->viewComponent = std::make_unique<ViewComponent>(this->view, this->defaultView);

    this->playerWindow = std::make_unique <gui::PlayerWindow>
    (
        this->warehouseCard, sf::Vector2f(65.f, 0.f), 
        sf::Vector2f(this->stateData->window->getSize().x * 3.f / 7.f, 1012.f), *this->player
    );
}

// Constructors/Destructors
GameState::GameState(StateData* state_data) : State(state_data), 
    keytimeMax(10.f), keytime(0.f), buff(false)
{
    this->initVariables();
    this->initKeybinds();
    this->initView();
    this->initMap();
    this->initPlayer();
    this->initPlayerCards();
    this->initButtons();
    this->initFont();
    this->initComponents();

    this->stage.setFont(this->AoT_Font);
    this->stage.setCharacterSize(70);
}

GameState::~GameState()
{
    this->map.reset();
    this->player.reset();
    deletePlayerCards();
    deleteButtons();
}

// Functions
void GameState::endState()
{
    std::cout << "End" << "\n";
}

void GameState::deletePlayerCards()
{
    for (auto* card : playerHand) 
    {
        delete card;
    }   
     
    playerHand.clear();
}

void GameState::deleteButtons()
{
    for(auto& it : buttons)
    {
        delete it.second;
    }
    buttons.clear();
}

const bool GameState::getKeytime()
{
    if (this->keytime >= keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}


void GameState::handleSecondStage()
{
    this->updateTitanButton();
    this->updateWarehouseButton();
}


bool GameState::isPlayerOnTitanCell() const
{
    return this->map->getCellType(this->map->playerIndexSearch(this->player->getPosition())) == Cell::CellType::Titan;
}

bool GameState::isPlayerOnBeastCell() const
{
    return this->map->getCellType(this->map->playerIndexSearch(this->player->getPosition())) == Cell::CellType::Beast;
}

bool GameState::isPlayerOnForestCell() const
{
    return this->map->getCellType(this->map->playerIndexSearch(this->player->getPosition())) == Cell::CellType::Forest;
}

bool GameState::isPlayerOnWarehouseCell() const
{
    return this->map->getCellType(this->map->playerIndexSearch(this->player->getPosition())) == Cell::CellType::Warehouse;
}


void GameState::updatePlayerWindow(const float &dt, const sf::Vector2i& mouse_pos_window)
{
    if (this->playerWindow)
    {   
        if (this->playerWindow->isShowWindow())
        {
            this->playerWindow->update(dt, mouse_pos_window);
        }
    }
}

void GameState::updateTitanButton()
{
    if (this->forestComponent)
    {
        bool can_interact = this->forestComponent->getFight();

        this->buttons["TITAN_BTN"]->setLock(!can_interact);

        if (this->buttons["TITAN_BTN"]->isReleased() && can_interact && !this->battleComponent->isBattleActive())
        {
            this->battleComponent->startBattle(this->buff);
        }
    }
    else
    {
        bool can_interact = this->isPlayerOnTitanCell();

        this->buttons["TITAN_BTN"]->setLock(!can_interact);

        if (this->buttons["TITAN_BTN"]->isReleased() && can_interact && !this->battleComponent->isBattleActive())
        {
            this->battleComponent->startBattle(this->buff);
        }
    }
}

void GameState::updateWarehouseButton()
{
    bool can_interact = this->isPlayerOnWarehouseCell();

    if (can_interact) 
    {
        if(!this->warehouseComponent)
        {
            this->warehouseComponent = std::make_unique<WarehouseComponent>();
        }
        this->buttons["WAREHOUSE_BTN"]->setLock(!can_interact);

        if (this->buttons["WAREHOUSE_BTN"]->isReleased() && can_interact && !this->warehouseComponent->isWarehouseActive())
        {
            this->warehouseComponent->startWarehouse(this->stage);
        }
    }
}

void GameState::updateForest()
{
    if (this->isPlayerOnForestCell())
    {
        if (!this->forestComponent)
        {
            this->forestComponent = std::make_unique<ForestComponent>(*this->map);
        }

        this->forestComponent->update(this->mousePosIndex, *this->buttons["TITAN_BTN"], this->getKeytime(), this->map->playerIndexSearch(this->player->getPosition()));

        this->buff = this->forestComponent->getBuff();
    }
    else
    {
        if (this->forestComponent)
        {
            this->forestComponent.reset();
        }
    }
}

void GameState::updateBeast(const float& dt)
{
    if (this->isPlayerOnBeastCell() /*&& this->movementComponent->shouldReact()*/)
    {
        if (!this->beastThrowComponent)
        {
            this->beastThrowComponent = std::make_unique<BeastThrowComponent>(sf::Vector2f(460.f, 130.f), sf::Vector2f(1005.f, 680.f));
        }

        this->beastThrowComponent->update(dt, this->mousePosWindow, *this->player, *this->buttons["DICE_BTN"]);
        
        if (!this->beastThrowComponent->isActiveBeast())
        {
            this->beastThrowComponent.reset();
            this->movementComponent->setReact(false);
        }
    }
    else
    {
        if (this->beastThrowComponent)
        {
            this->beastThrowComponent.reset();
        }
    }
}

void GameState::updateKeybinds(const float &dt)
{
    this->checkForQuit();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->getKeytime())
    {
        this->movementComponent->confirmMovement();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("RESPONSE"))) && this->getKeytime())
    {
        this->movementComponent->handleResponseKey();
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PLAYER_WINDOW"))) && !this->playerWindow->isShowWindow() && this->getKeytime())
    {
        this->playerWindow->setShowWindow(true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PLAYER_WINDOW"))) && this->playerWindow->isShowWindow() && this->getKeytime())
    {
        this->playerWindow->setShowWindow(false);
    }
}

void GameState::updateGui(const float &dt, const sf::Vector2i& mouse_pos_window)
{
    for (auto &it : this->playerHand)
	{
		it->update(dt, mouse_pos_window);
	}

    for (auto& it : this->buttons)
	{
		it.second->update(mouse_pos_window, dt);
	}
}

void GameState::updateKeyTime(const float &dt)
{
    if (this->keytime < this->keytimeMax)
	{
		this->keytime += 100.f * dt;
	}
}

void GameState::updateMousePosIndex()
{
    this->mousePosIndex = sf::Vector2i
    (
        this->map->indexSearch(sf::Vector2f(static_cast<float>(this->mousePosView.x), static_cast<float>(this->mousePosView.y))).x,
        this->map->indexSearch(sf::Vector2f(static_cast<float>(this->mousePosView.x), static_cast<float>(this->mousePosView.y))).y
    );
}

void GameState::update(const float &dt)
{
    this->updateKeyTime(dt);

    this->updateKeybinds(dt);

    this->updateMousePositions(&this->view);

    this->updateMousePosIndex();

    this->updateGui(dt, this->mousePosWindow);

    this->updatePlayerWindow(dt, this->mousePosWindow);

    this->updateForest();



    if (!this->movementComponent->shouldReact()) 
    {
        this->stage.setString("First Stage");
        this->movementComponent->handleFirstStage(this->mousePosView, this->getKeytime());
    } 
    else
    {
        if (!this->battleComponent->isBattleActive() && (this->warehouseComponent && !this->warehouseComponent->isWarehouseActive()))
        {
            this->stage.setString("Second Stage");
        }

        this->handleSecondStage();

        this->updateBeast(dt);
    }
    
    this->stage.setPosition
    (
        static_cast<float>(this->window->getSize().x) / 2.f - this->stage.getGlobalBounds().width / 2.f, 
        5.f
    );

    this->viewComponent->update(this->keybinds, this->getKeytime());
    
    if (this->battleComponent->isBattleActive())
    {
        this->battleComponent->update(*this->buttons["DICE_BTN"], dt, this->mousePosWindow);
    }

    if (this->warehouseComponent && this->warehouseComponent->isWarehouseActive())
    {
        this->warehouseComponent->update(dt, this->mousePosWindow, this->stage, this->diceResult, *this->buttons["DICE_BTN"]);

        if (this->warehouseComponent->getCanGetSelectCard())
        {            
            auto new_card = this->warehouseComponent->getSelectCard();
            if (new_card) 
            {
                this->warehouseCard.push_back(std::move(new_card));
            }
        } 

        if(!this->warehouseComponent->isWarehouseActive())
        {
            this->warehouseComponent.reset();
        }  
    }
}


void GameState::renderGui(sf::RenderTarget &target)
{
    for (int i = 0; i < this->maxCard; ++i) 
    {
        this->playerHand[i]->render(target);
    }

    for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void GameState::render(sf::RenderTarget *target)
{
    if (!target)
	{
		target = this->window;
	}

    target->draw(this->background);
    
    target->setView(this->view);

    this->map->render(*target);

    this->player->render(*target);

    target->setView(this->window->getDefaultView());

    this->renderGui(*target);

    target->draw(this->stage);

    if (this->battleComponent)
    {
        this->battleComponent->render(target);
    }

    if (this->warehouseComponent)
    {
        this->warehouseComponent->render(target);
    }

    if(!this->buttons["DICE_BTN"]->getLock())
    {
        target->draw(this->diceResult);
    }

    if (this->playerWindow)
    {
        if (this->playerWindow->isShowWindow())
        {
            this->playerWindow->render(target);
        }
    }

    if (this->beastThrowComponent)
    {
        this->beastThrowComponent->render(target);
    }
   // Show mouse coordinate
	sf::Text mouse_text;
	std::stringstream ss;
	mouse_text.setPosition(this->mousePosWindow.x, this->mousePosWindow.y - 50);
	mouse_text.setFont(this->font);
	mouse_text.setCharacterSize(15);

	ss << this->map->indexSearch(sf::Vector2f(static_cast<float>(this->mousePosView.x), static_cast<float>(this->mousePosView.y))).x << ":" 
       << this->map->indexSearch(sf::Vector2f(static_cast<float>(this->mousePosView.x), static_cast<float>(this->mousePosView.y))).y;
	mouse_text.setString(ss.str());

	target->draw(mouse_text);
}
