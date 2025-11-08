#include "Gui.h"
#include <random>
#include "../Entities/Player.h"
#include <iostream>
#include "../Entities/Titan.h"
#include "../GameLogic/Battle/TitanBattle.h"


/*------------------------------------CLASS CARD----------------------------------------------*/

gui::Card::Card()
{
    if (!this->AoT_Font.loadFromFile("Resources/Fonts/AoT_Font.ttf"))
	{
    	exit(1);
    }

    if (!this->font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
	{
    	exit(1);
    }

    this->keytime = 0.f;
    this->keytimeMax = 7.f;

    this->pressing = true;

    this->shapeTexture = NULL; //remove later
}

gui::Card::~Card()
{

}

sf::Vector2f gui::Card::getPosition()
{
    return this->position;
}

sf::Vector2f gui::Card::getSize()
{
    return this->shape.getSize();
}

const bool gui::Card::getKeytime()
{
    if (this->keytime >= keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

const bool gui::Card::isHover() 
{
    if (this->cardState == CardState::CARD_HOVER)
    {
        return true;
    }
    return false;
}

void gui::Card::dontHover()
{
    this->cardState = CardState::CARD_IDLE;
    this->pressing = true;
}

const bool gui::Card::checkPressing()
{
    return this->pressing;
}

void gui::Card::canPress()
{
    this->pressing = true;
}

void gui::Card::cantPress()
{
    this->pressing = false;
}

void gui::Card::updateKeyTime(const float &dt)
{
    if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
}

CardState gui::Card::getCardState()
{
    return this->cardState;
}

/*------------------------------------CLASS PLAYER CARD----------------------------------------------*/

void gui::PlayerCard::initVariables()
{
    if (this->route[0] == 'f')
    {
        this->routeText.setString("TP");
        this->routeText.setFont(this->AoT_Font);
        this->routeText.setCharacterSize(50);
        this->routeText.setFillColor(sf::Color::Green);

    }

    else if (this->route[0] == 'w')
    {
        this->routeText.setString("TP");
        this->routeText.setFont(this->AoT_Font);
        this->routeText.setCharacterSize(50);
        this->routeText.setFillColor(sf::Color::Yellow);

    }

    else if (this->route[0] == 't')
    {
        this->routeText.setString("TP");
        this->routeText.setFont(this->AoT_Font);
        this->routeText.setCharacterSize(50);
        this->routeText.setFillColor(sf::Color::Red);
    }

    else
    {   this->titleText.setString("HELLO");
        this->titleText.setFont(this->AoT_Font);
        this->titleText.setCharacterSize(22);

        if(this->route[0] == 'd')
        {
            this->titleText.setFillColor(sf::Color::Red);
        }
        else this->titleText.setFillColor(sf::Color::Black);


        this->routeText.setString(this->route);
        this->routeText.setFont(this->font);
        this->routeText.setCharacterSize(50);
        this->routeText.setFillColor(sf::Color::Red);
    }

    this->gost = false;
}

gui::PlayerCard::PlayerCard(std::string route) : Card(), route(route)
{
    this->shape.setSize(sf::Vector2f(150.0f, 200.0f)); 
    this->shape.setOutlineThickness(5);
    this->shape.setOutlineColor(sf::Color::Black);  

    initVariables();

    this->cardState = CardState::CARD_IDLE;
}

gui::PlayerCard::PlayerCard(const PlayerCard &other)
{
    this->AoT_Font = other.AoT_Font;
    this->cardState = other.cardState;
    this->font = other.font;
    this->shape = other.shape;
    this->route = other.route;
    this->keytime = other.keytime;
    this->keytimeMax = other.keytimeMax;
    this->titleText = other.titleText;
    this->routeText = other.routeText;
    this->gost = other.gost;
    this->pressing = other.pressing;
}

gui::PlayerCard::PlayerCard(PlayerCard &&other) noexcept
{
    this->AoT_Font = std::move(other.AoT_Font);
    this->cardState = std::move(other.cardState);
    this->font = std::move(other.font);
    this->shape = std::move(other.shape);
    this->route = std::move(other.route);
    this->keytime = std::move(other.keytime);
    this->keytimeMax = std::move(other.keytimeMax);
    this->titleText = std::move(other.titleText);
    this->routeText = std::move(other.routeText);
    this->gost = std::move(other.gost);
    this->pressing = std::move(other.pressing);
}

gui::PlayerCard &gui::PlayerCard::operator=(const PlayerCard &other)
{
    if (this != &other)
    {
        this->AoT_Font = other.AoT_Font;
        this->cardState = other.cardState;
        this->font = other.font;
        this->shape = other.shape;
        this->route = other.route;
        this->keytime = other.keytime;
        this->keytimeMax = other.keytimeMax;
        this->titleText = other.titleText;
        this->routeText = other.routeText;
        this->gost = other.gost;
        this->pressing = other.pressing;
    }

    return *this;
}

gui::PlayerCard &gui::PlayerCard::operator=(PlayerCard &&other) noexcept
{
    if (this != &other)
    {
        this->AoT_Font = std::move(other.AoT_Font);
        this->cardState = std::move(other.cardState);
        this->font = std::move(other.font);
        this->shape = std::move(other.shape);
        this->route = std::move(other.route);
        this->keytime = std::move(other.keytime);
        this->keytimeMax = std::move(other.keytimeMax);
        this->titleText = std::move(other.titleText);
        this->routeText = std::move(other.routeText);
        this->gost = std::move(other.gost);
        this->pressing = std::move(other.pressing);
    }

    return *this;
}

gui::PlayerCard::~PlayerCard()
{

}

void gui::PlayerCard::setPosition(float posX, float posY)
{
    this->shape.setPosition(sf::Vector2f(posX, posY));

    this->routeText.setPosition
	(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->routeText.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + 90
	);

    this->titleText.setPosition
	(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->titleText.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + 15
	);

    this->position = sf::Vector2f(posX, posY);
}

void gui::PlayerCard::swap(PlayerCard &other) noexcept
{
    std::swap(this->AoT_Font, other.AoT_Font);
    std::swap(this->cardState, other.cardState);
    std::swap(this->font, other.font);
    std::swap(this->shape, other.shape);
    std::swap(this->route, other.route);
    std::swap(this->keytime, other.keytime);
    std::swap(this->keytimeMax, other.keytimeMax);
    std::swap(this->titleText, other.titleText);
    std::swap(this->routeText, other.routeText);
    std::swap(this->gost, other.gost);
    std::swap(this->pressing, other.pressing);
}

void gui::PlayerCard::setGost(bool gost)
{
    this->gost = gost;
}

bool gui::PlayerCard::getGost()
{
    return this->gost;
}

std::string gui::PlayerCard::getRoute()
{
    return this->route;
}

void gui::PlayerCard::update(const float &dt, const sf::Vector2i &mouse_pos_window)
{
    this->updateKeyTime(dt);

    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window)))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isHover() && this->getKeytime() && this->checkPressing())              
        {                    
            this->cardState = CardState::CARD_HOVER;                                                                                                     
        }

        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->isHover() && this->getKeytime())
        {
            this->cardState = CardState::CARD_IDLE;
        }
    }

    switch (cardState)
    {
    case CardState::CARD_IDLE:
        this->shape.setOutlineColor(sf::Color::Black);
        break;

    case CardState::CARD_HOVER:
        this->shape.setOutlineColor(sf::Color::Red);
        break;
    
    default:
        break;
    }
}

void gui::PlayerCard::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
    target.draw(this->titleText);
    target.draw(this->routeText);
}


/*------------------------------------CLASS WAREHOUSE CARD----------------------------------------------*/

void gui::WarehouseCard::initVariables()
{
    if (this->type == WarehouseCardType::STALL)
    {
        this->title = "Stall";
        this->info  = "---";
    }

    else if (this->type == WarehouseCardType::AMMUNITION)
    {
        this->title = "Ammunition";
        this->info  = "===";
    }

    else if (this->type == WarehouseCardType::MEDICINE_CHEST)
    {
        this->title = "Medicine chest";
        this->info  = "----";
    }

    this->shape.setSize(sf::Vector2f(180.f, 290.f));

    this->shape.setFillColor(sf::Color::Red);
    this->shape.setOutlineThickness(3);

    this->cardState = CardState::CARD_IDLE;
    
    this->titleText.setString(title);
    this->infoText.setString(info);

    this->titleText.setFont(this->AoT_Font);
    this->infoText.setFont(this->AoT_Font);
}


gui::WarehouseCard::WarehouseCard(WarehouseCardType type) : Card(), type(type)
{
    this->initVariables();
}

gui::WarehouseCard &gui::WarehouseCard::operator=(const WarehouseCard &other)
{
    if (this != &other)
    {
        this->AoT_Font = other.AoT_Font;
        this->cardState = other.cardState;
        this->font = other.font;
        this->shape = other.shape;
        this->info = other.info;
        this->keytime = other.keytime;
        this->keytimeMax = other.keytimeMax;
        this->titleText = other.titleText;
        this->infoText = other.infoText;
        this->pressing = other.pressing;
        this->type = other.type;
        this->index = other.index;
        this->title = other.title;
        this->shapeTexture = other.shapeTexture;
        this->position = other.position;
    }

    return *this;
}

gui::WarehouseCard::~WarehouseCard()
{
}


void gui::WarehouseCard::setPosition(float posX, float posY)
{
    this->shape.setPosition(sf::Vector2f(posX, posY));

    this->infoText.setPosition
	(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->infoText.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + 90
	);

    this->titleText.setPosition
	(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->titleText.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + 15
	);
}

void gui::WarehouseCard::setIndex(int index)
{
    this->index = index;
}

int gui::WarehouseCard::getIndex()
{
    return this->index;
}

void gui::WarehouseCard::setWarehouseCardType(WarehouseCardType type)
{
    this->type = type;
}

WarehouseCardType gui::WarehouseCard::getWarehouseCardType()
{
    return this->type;
}

void gui::WarehouseCard::useCard()
{
}

void gui::WarehouseCard::update(const float& dt, const sf::Vector2i& mouse_pos_window)
{
    this->updateKeyTime(dt);

    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window)))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isHover() && this->getKeytime() && this->checkPressing())              
        {                    
            this->pressing = false;
            this->cardState = CardState::CARD_HOVER;                                                                                                     
        }

        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->isHover() && this->getKeytime())
        {
            this->pressing = true;
            this->cardState = CardState::CARD_IDLE;
        }
    }

    switch (cardState)
    {
    case CardState::CARD_IDLE:
        this->shape.setOutlineColor(sf::Color::Black);
        break;

    case CardState::CARD_HOVER:
        this->shape.setOutlineColor(sf::Color::White);
        break;
    
    default:
        break;
    }
}

void gui::WarehouseCard::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
    target.draw(this->titleText);
    target.draw(this->infoText);
}

/*------------------------------------CLASS DECK----------------------------------------------*/

gui::Deck::Deck()
{
    std::string routes[] = 
    {
        "656", "165", "234", "5", "111", "44344", "11611", "345", "34343", "43",
        "55", "212", "2222", "66656", "2", "21211", "44545", "32332", "1656", "56",
        "3234", "61616", "56656", "323",
                            
        "d32", "d61", "d655", "d5555", "d444", "d216", "d32333", "d22",

        "f1", "f2", "t", "w"
    }; 

    std::string testWarehouse[] = 
    {
        "w", "w", "w", "w", "w"
    };

    std::string testForest[] = 
    {
        "f", "f", "f", "f", "f"
    };

    std::string testTitan[] = 
    {
        "t", "t", "t", "t", "t"
    };

    std::string testBeast[] = 
    {
        "b", "b", "b", "b", "b"
    };

    for (const auto& route : testTitan) {
        cards.emplace_back(route);
    }   
        
    this->shuffle();
}

gui::Deck::~Deck()
{
}

void gui::Deck::addCard(PlayerCard other)
{
    this->cards.push_back(other);
}

bool gui::Deck::isEmpty()
{
    return this->cards.empty();
}

std::string gui::Deck::distribution()
{
    if (cards.empty()) 
        throw std::runtime_error("Deck is empty");
    
    std::string route = cards.back().getRoute();  
    cards.pop_back();

    return route; 
}

void gui::Deck::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->cards.begin(), this->cards.end(), g);
}

void gui::Deck::clear()
{
    this->cards.clear();
}

namespace std 
{
    template <>
    void swap(gui::PlayerCard& a, gui::PlayerCard& b) noexcept 
    {
        a.swap(b);
    }
}

/*------------------------------------CLASS TitanDeck----------------------------------------------*/

gui::TitanDeck::TitanDeck()
{
    char types[] = 
    {
        '3', '3', '3', '1', '1', '3', '3', '3', '2', '2', '2', '1', '1', '1',
        
        '1', '1', '2', '2', '3', '3', '1', '1', '1', '2', '2', '2', '2', '2', '2', '2',
    }; 

    for (const auto& type : types) {
        titanDeck.emplace_back(type);
    }   
        
    this->shuffle();
}

gui::TitanDeck::~TitanDeck()
{
}

void gui::TitanDeck::addCard(char other)
{
    this->titanDeck.push_back(other);
}

void gui::TitanDeck::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->titanDeck.begin(), this->titanDeck.end(), g);
}

void gui::TitanDeck::clear()
{
    this->titanDeck.clear();
}

bool gui::TitanDeck::isEmpty()
{
    return this->titanDeck.empty();
}

char gui::TitanDeck::getLastType()
{
    return this->titanDeck.back();
}

void gui::TitanDeck::popType()
{
    this->titanDeck.pop_back();
}

namespace std 
{
    template <>
    void swap(char& a, char& b) noexcept 
    {
        char temp;
        temp = a;
        a = b;
        b = temp;
    }
}

/*------------------------------------CLASS BUTTON----------------------------------------------*/

gui::Button::Button
    (float x, float y, float width, float height, 
     sf::Font *font, std::string text, unsigned character_size, bool lock,
     sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
     sf::Color idle_color, sf::Color hover_color, sf::Color active_color, 
     sf::Color outline_idle_color, 
     sf::Color outline_hover_color, 
     sf::Color outline_active_color
    )
    : keytimeMax(1.f), keytime(0.f), lock(lock), isBeingHeld(false)
    {
    this->buttonState = BTN_IDLE;

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineThickness(3.f);
	this->shape.setOutlineColor(outline_active_color);
  

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->idleColor);
	this->text.setCharacterSize(character_size);
	this->text.setPosition
	(
        this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2,
        this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2
	);
}

gui::Button::~Button()
{
}

const bool gui::Button::isPressed()
{
    if (this->buttonState == ButtonState::BTN_ACTIVE)
    {
        this->buttonState = ButtonState::BTN_IDLE;
        return true;
    }
    return false;
}

const std::string gui::Button::getText() const
{
    return this->text.getString();
}

const bool gui::Button::getKeytime()
{
    if (this->keytime >= keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

void gui::Button::updateKeyTime(const float &dt)
{
    if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
}

void gui::Button::setText(const std::string text)
{
    this->text.setString(text);
}

void gui::Button::update(const sf::Vector2i &mouse_pos_window, const float &dt)
{
    this->updateKeyTime(dt);

	this->buttonState = ButtonState::BTN_IDLE;

    if(!lock)
    {
	    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window)))
	    {
		    this->buttonState = ButtonState::BTN_HOVER;

     		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	    	{
		    	this->buttonState = ButtonState::BTN_ACTIVE;
		    }
    	}
    }

	switch (this->buttonState)
	{
	case ButtonState::BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case ButtonState::BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case ButtonState::BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Black);

		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	
	target.draw(this->shape);
	target.draw(this->text);
	
}

const bool gui::Button::getLock() const
{
    return this->lock;
}

const bool gui::Button::isReleased()
{
    if (this->buttonState == ButtonState::BTN_HOVER && isBeingHeld)
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isBeingHeld = false;
            return true;
        }
    }
    else if (this->buttonState == ButtonState::BTN_ACTIVE)
    {
        isBeingHeld = true;
    }
    return false;
}

void gui::Button::setLock(const bool lock)
{
    this->lock = lock;
}


/*------------------------------------CLASS INTERACTIVE WINDOW----------------------------------------------*/

void gui::InteractiveWindow::initFont()
{
    if (!this->aotFont.loadFromFile("Resources/Fonts/AoT_Font.ttf"))
	{
    	exit(1);
    }

    if (!this->font.loadFromFile("Resources/Fonts/Dosis-Light.ttf"))
	{
    	exit(1);
    }
}


gui::InteractiveWindow::InteractiveWindow()
{
    initFont();
}

gui::InteractiveWindow::~InteractiveWindow()
{

}

void gui::InteractiveWindow::setShowWindow(bool show)
{
    this->showWindow = show;
}

const bool gui::InteractiveWindow::isShowWindow() const
{
    return this->showWindow;
}

sf::Vector2f gui::InteractiveWindow::getSize()
{
    return sf::Vector2f(this->window.getGlobalBounds().width, this->window.getGlobalBounds().height);
}

void gui::InteractiveWindow::deleteButtons()
{
    for(auto it : buttons)
    {
        delete it.second;
    }
}


/*------------------------------------CLASS WAREHOUSE INTERACTIVE WINDOW----------------------------------------------*/

void gui::WarehouseInteractiveWindow::initBackground()
{
    this->windowBackground.setSize
    (
        sf::Vector2f
        (
            this->window.getSize().x,
            this->window.getSize().y
        )
    );

    this->windowBackground.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x,
            this->window.getPosition().y
        )
    );

    this->windowBackground.setOutlineThickness(3);
    this->windowBackground.setOutlineColor(sf::Color::Black);

    this->windowBackground.setFillColor(sf::Color(160, 82, 45));
}

void gui::WarehouseInteractiveWindow::initWindow()
{
    this->window.setSize(this->sizeWindow);
    this->window.setPosition(this->positionWindow);
    this->window.setFillColor(sf::Color::Black);
}

void gui::WarehouseInteractiveWindow::initButtons()
{
    this->buttons["OK"] = new gui::Button
    (
        this->window.getPosition().x + this->window.getSize().x / 2.f - 60.f,
        (this->window.getPosition().y + this->window.getSize().y) * 9.f / 10.f,
        120.f, 60.f,
        &this->aotFont, "OK", 30, false,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );
}

void gui::WarehouseInteractiveWindow::initVariables()
{
    this->showWindow = true;
    this->chose = false;
    //this->startTimer = false;
    //this->endTimer = false;
    this->diceButtonWasPressed = false;
    this->waitingForDelay = false;

    this->elapsedTime = 0.0f;
}

void gui::WarehouseInteractiveWindow::initText()
{
    this->title = "Warehouse";

    switch (numberCard)
    {
    case 0:
        this->info = "Bye Bye!";
        break;

    case 1:
        this->info = "Take this card";
        break;

    case 2:
        this->info = "Choose one of two cards";
        break;

    case 3:
        this->info = "Choose one of three cards!";
        break;
    
    default:
        break;
    }
    
    this->titleText.setString(this->title);
    this->infoText.setString(this->info);

    this->titleText.setFont(this->aotFont);
    this->infoText.setFont(this->aotFont);

    titleText.setCharacterSize(40);
    infoText.setCharacterSize(32);

    titleText.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + this->window.getSize().x / 2.f - this->titleText.getGlobalBounds().width / 2.f,
            this->window.getPosition().y + 2.f
        )
    );

    infoText.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + this->window.getSize().x / 2.f - this->infoText.getGlobalBounds().width / 2.f,
            this->titleText.getPosition().y + this->titleText.getGlobalBounds().height + 25.f
        )
    );
}

void gui::WarehouseInteractiveWindow::initTexture()
{
}

void gui::WarehouseInteractiveWindow::initCard()

{
    switch (numberCard)
    {
    case 1:
        this->cards.push_back(std::make_unique<WarehouseCard>(WarehouseCardType::STALL));
        this->cards[0]->setPosition
        (
            this->window.getPosition().x + this->window.getGlobalBounds().width / 2.f - this->cards[0]->getSize().x / 2.f, 
            this->window.getPosition().y + this->window.getGlobalBounds().height * 3.f / 10.f
        );
        this->cards[0]->setIndex(0);

        break;

    case 2:
        this->cards.push_back(std::make_unique<WarehouseCard>(WarehouseCardType::STALL));
        this->cards.push_back(std::make_unique<WarehouseCard>(WarehouseCardType::AMMUNITION));
        
        for (int i = 0; i < this->numberCard; i++)
        {
            this->cards[i]->setPosition
            (
                this->window.getPosition().x + this->window.getGlobalBounds().width / 3.f * static_cast<float>(i + 1) - this->cards[i]->getSize().x / 2.f,
                this->window.getPosition().y + this->window.getGlobalBounds().height * 3.f / 10.f
            );
            this->cards[i]->setIndex(i);
        }

        break;

    case 3:
        this->cards.push_back(std::make_unique<WarehouseCard>(WarehouseCardType::STALL));
        this->cards.push_back(std::make_unique<WarehouseCard>(WarehouseCardType::AMMUNITION));
        this->cards.push_back(std::make_unique<WarehouseCard>(WarehouseCardType::MEDICINE_CHEST));

        for (int i = 0; i < this->numberCard; i++)
        {
            this->cards[i]->setPosition
            (
                this->window.getPosition().x + this->window.getGlobalBounds().width / 4.f * static_cast<float>(i + 1) - this->cards[i]->getSize().x / 2.f,
                this->window.getPosition().y + this->window.getGlobalBounds().height * 3.f / 10.f
            );
            this->cards[i]->setIndex(i);
        }

        break;
    
    default:
        break;
    }
}


void gui::WarehouseInteractiveWindow::setIndexSelectCard(int index)
{
    this->indexSelectCard = index;
}

int gui::WarehouseInteractiveWindow::getIndexSelectCard()
{
    return this->indexSelectCard;
}


gui::WarehouseInteractiveWindow::WarehouseInteractiveWindow(int number_card, sf::Vector2f position_window, sf::Vector2f size_window) : InteractiveWindow(),
    numberCard(number_card)
{
    this->positionWindow = position_window;
    this->sizeWindow = size_window;

    this->initWindow();
    this->initTexture();
    this->initBackground();
    this->initVariables();
    this->initButtons();
    this->initText();
    this->initCard();
}

gui::WarehouseInteractiveWindow::~WarehouseInteractiveWindow()
{
    this->cards.clear();

    for(auto it : buttons)
    {
        delete it.second;
    }
}


WarehouseCardType gui::WarehouseInteractiveWindow::getSelectType()
{
    return this->selectType;
}

std::unique_ptr<gui::WarehouseCard> gui::WarehouseInteractiveWindow::getSelectCard()
{
    for (int i = 0; i < this->numberCard; i++)
    {
        if (this->cards[i]->getIndex() == this->indexSelectCard)
        {
            this->cards[i]->dontHover();
            return std::move(this->cards[i]);
        }
    }
    throw std::runtime_error("Card not found");
}

bool gui::WarehouseInteractiveWindow::isCardEmpty()
{
    return this->cards.empty();
}

void gui::WarehouseInteractiveWindow::updateCard(const float& dt, const sf::Vector2i& mouse_pos_window)
{
    for (int i = 0; i < this->numberCard; i++)
    {
        this->cards[i]->update(dt, mouse_pos_window);
    }
}

void gui::WarehouseInteractiveWindow::updateElapsedTime()
{
}

void gui::WarehouseInteractiveWindow::updateButtons(const float &dt, const sf::Vector2i &mouse_pos_window)
{
    for(auto it : this->buttons)
    {
        it.second->update(mouse_pos_window, dt);
    }   
}

void gui::WarehouseInteractiveWindow::update(const float &dt, const sf::Vector2i &mouse_pos_window)
{
    this->updateCard(dt, mouse_pos_window);
    this->updateButtons(dt, mouse_pos_window);

    for (int i = 0; i < numberCard; i++)
    {
        if (this->cards[i]->isHover())
        {
            if (this->buttons["OK"]->isReleased())
            {
                this->selectType = this->cards[i]->getWarehouseCardType();
                this->indexSelectCard = this->cards[i]->getIndex();
                this->showWindow = false;
                break;
            }
            else continue;
        }
    }

    if (this->cards.empty())
    {
        if (this->buttons["OK"]->isReleased())
        {
            this->showWindow = false;
        }
    }      
}


void gui::WarehouseInteractiveWindow::renderCard(sf::RenderTarget &target)
{
    for (int i = 0; i < this->numberCard; i++)
    {
        this->cards[i]->render(target);
    }
}

void gui::WarehouseInteractiveWindow::renderButtons(sf::RenderTarget &target)
{
    for (auto it : this->buttons)
    {
        it.second->render(target);
    }
}

void gui::WarehouseInteractiveWindow::render(sf::RenderTarget *target)
{
    target->draw(this->window);
    target->draw(this->windowBackground);
    target->draw(this->infoText);
    target->draw(this->titleText);

    this->renderButtons(*target);
    this->renderCard(*target);
}

/*------------------------------------CLASS PLAYER WINDOW----------------------------------------------*/

void gui::PlayerWindow::initVariables()
{
    this->showWindow = false;
    this->choiceCard = false;
    this->choiceSkill = false;
    this->numberCard = this->inventoryCards.size();
}

void gui::PlayerWindow::initTexture()
{
    if(!this->iconTexture.loadFromFile("Resources/Picture/frog.png"))
	{
		exit(1);
	}
}

void gui::PlayerWindow::initWindow()
{
    this->window.setSize(this->sizeWindow);
    this->window.setPosition(this->positionWindow);
    this->window.setFillColor(sf::Color::Black);
}

void gui::PlayerWindow::initBackground()
{
    this->windowBackground.setSize
    (
        this->window.getSize()
    );

    this->windowBackground.setPosition
    (
        this->window.getPosition()
    );

    this->windowBackground.setFillColor(sf::Color(160, 82, 45));
    this->windowBackground.setOutlineColor(sf::Color::Black);
    this->windowBackground.setOutlineThickness(3);
}

void gui::PlayerWindow::initIcon()
{
    this->icon.setTexture(&this->iconTexture);

    this->icon.setPosition
    (
        this->window.getPosition()
    );

    this->icon.setSize
    (
        sf::Vector2f
        (
            this->window.getSize().x * 9.f  / 21.f,
            this->window.getSize().y * 10.f / 27.f
        )
    );
}

void gui::PlayerWindow::initText()
{
    this->titleText.setFont(this->aotFont);
    this->infoText.setFont(this->aotFont);
    this->descriptionText.setFont(this->aotFont);
    this->passiveSkillNameText.setFont(this->aotFont);
    this->passiveSkillDescriptionText.setFont(this->aotFont);
    this->activeSkillNameText.setFont(this->aotFont);
    this->activeSkillDescriptionText.setFont(this->aotFont);
    this->inventoryText.setFont(this->aotFont);

    this->title = this->player.getName();
    this->info = this->player.getDescription();
    this->description = "Description";
    this->passiveSkillName = "Passive:";
    this->activeSkillName = "Active:";
    this->passiveSkillDescription = "Inconspicuous";
    this->activeSkillDescription = "Fuck with tongue";  
    this->inventory = "Inventory";

    this->titleText.setString(this->title);
    this->infoText.setString(this->info);
    this->descriptionText.setString(this->description);
    this->passiveSkillNameText.setString(this->passiveSkillName);
    this->passiveSkillDescriptionText.setString(this->passiveSkillDescription);
    this->activeSkillNameText.setString(this->activeSkillName);
    this->activeSkillDescriptionText.setString(this->activeSkillDescription);
    this->inventoryText.setString(this->inventory);

    this->titleText.setPosition
    (
        sf::Vector2f
        (
            this->icon.getPosition().x + this->icon.getGlobalBounds().width + 50,
            this->window.getPosition().y + 20
        )
    );

    this->descriptionText.setPosition
    (
        sf::Vector2f
        (
            ((this->window.getPosition().x + this->window.getGlobalBounds().width + this->icon.getPosition().x + this->icon.getGlobalBounds().width) / 2.f) - this->descriptionText.getGlobalBounds().width / 2,
           this->titleText.getPosition().y + 90.f
        )
    );

    this->infoText.setPosition
    (
        sf::Vector2f
        (
            this->icon.getPosition().x + this->icon.getGlobalBounds().width + 50.f,
            this->descriptionText.getPosition().y + 50.f
        )
    );

    this->passiveSkillNameText.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + 30.f,
            this->icon.getPosition().y + this->icon.getGlobalBounds().height + 50.f
        )
    );

    this->passiveSkillDescriptionText.setPosition
    (
        sf::Vector2f
        (
            this->passiveSkillNameText.getPosition().x + this->passiveSkillNameText.getGlobalBounds().width + 10.f,
            this->passiveSkillNameText.getPosition().y
        )
    );

    this->activeSkillNameText.setPosition
    (
        sf::Vector2f
        (
            this->passiveSkillNameText.getPosition().x,
            this->passiveSkillNameText.getPosition().y + 60.f
        )
    );

    this->activeSkillDescriptionText.setPosition
    (
        sf::Vector2f
        (
            this->activeSkillNameText.getPosition().x + this->activeSkillNameText.getGlobalBounds().width + 10.f,
            this->activeSkillNameText.getPosition().y
        )
    );

    this->inventoryText.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + this->window.getSize().x / 2.f - this->inventoryText.getGlobalBounds().width / 2.f,
            this->activeSkillNameText.getPosition().y + 50.f
        )
    );
}

void gui::PlayerWindow::initInventoryCard()
{
    this->updatePositionCards();
}

void gui::PlayerWindow::initHealthLine()
{
    if(!this->healthLine.empty())
    {    
        for(size_t i = 0; i < this->player.getHealth(); i++)
        {
            this->healthLine[i].setPosition
            (
                this->titleText.getPosition().x + this->titleText.getGlobalBounds().width + (i * 50), this->titleText.getPosition().y
            );
        }
    }
}

void gui::PlayerWindow::initButtons()
{
    this->buttons["USE_SKILL"] = new gui::Button
    (
        this->window.getPosition().x + this->window.getSize().x - 63.f,
        this->activeSkillNameText.getPosition().y + 10.f,
        60.f, 30.f,
        &this->aotFont, "Skill", 20, false,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );

    this->buttons["USE_CARD"] = new gui::Button
    (
        (this->window.getPosition().x + this->window.getSize().x) / 2.f - 30.f,
        this->window.getPosition().y + this->window.getSize().y - 33.f,
        60.f, 30.f,
        &this->aotFont, "Use", 20, false,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );
}


gui::PlayerWindow::PlayerWindow(std::vector <std::unique_ptr <WarehouseCard> >& cards, sf::Vector2f position_window, sf::Vector2f size_window, Player& player) : InteractiveWindow(),
    inventoryCards(cards), player(player), healthLine(this->player.getHealthLine())
{
    this->positionWindow = position_window;
    this->sizeWindow = size_window;

    this->initVariables();
    this->initTexture();
    this->initWindow();
    this->initBackground();
    this->initIcon();
    this->initText();
    this->initInventoryCard();
    this->initButtons();
    this->initHealthLine();
}

gui::PlayerWindow::~PlayerWindow()
{
    this->deleteButtons();
}


void gui::PlayerWindow::updatePositionCards()
{
    this->numberCard = this->inventoryCards.size();

    if (!this->inventoryCards.empty())
    {
        switch (this->numberCard)
        {
        case 1:
            this->inventoryCards[0]->setPosition
            (
                this->window.getPosition().x + this->window.getSize().x / 2.f - this->inventoryCards[0]->getSize().x / 2.f,
                this->inventoryText.getPosition().y + 60.f
            );

            break;

        case 2:
            for (int i = 0; i < this->numberCard; i++)
            {
                this->inventoryCards[i]->setPosition
                (
                    (this->window.getPosition().x + this->window.getGlobalBounds().width) / 3.f * static_cast<float>(i + 1) - this->inventoryCards[i]->getSize().x / 2.f,
                    this->inventoryText.getPosition().y + 60.f
                );
            }
            
            break;

        case 3:
            for (int i = 0; i < this->numberCard; i++)
            {
                this->inventoryCards[i]->setPosition
                (
                    (this->window.getPosition().x + this->window.getGlobalBounds().width) / 4.f * static_cast<float>(i + 1) - this->inventoryCards[i]->getSize().x / 2.f,
                    this->inventoryText.getPosition().y + 60.f
                );
            }
            
            break;
        
        default:
            if (this->numberCard > 3)
            {
                std::cout<<"HelloUpdateCardPos"<<std::endl;
                for (int i = 0; i < 3; i++)
                {
                    this->inventoryCards[i]->setPosition
                    (
                        (this->window.getPosition().x + this->window.getGlobalBounds().width) / 4.f * static_cast<float>(i + 1) - this->inventoryCards[i]->getSize().x / 2.f,
                        this->inventoryText.getPosition().y + 60.f
                    );
                }
                break;
            }
            break;
        }
    }
}

void gui::PlayerWindow::updateCards(const float &dt, const sf::Vector2i &mouse_pos_window)
{
    if (!this->inventoryCards.empty())
    {
        this->updatePositionCards();
        
        this->numberCard = this->inventoryCards.size();

        for (int i = 0; i < this->numberCard; i++)
        {
            this->inventoryCards[i]->update(dt, mouse_pos_window);
        }
    }
}

void gui::PlayerWindow::updateButtons(const float &dt, const sf::Vector2i &mouse_pos_window)
{
    for (auto it : this->buttons)
    {
        it.second->update(mouse_pos_window, dt);
    } 
}

void gui::PlayerWindow::updateElapsedTime()
{
}

void gui::PlayerWindow::update(const float &dt, const sf::Vector2i &mouse_pos_window)
{
    this->updateCards(dt, mouse_pos_window);
    this->updateButtons(dt, mouse_pos_window);

    if (this->numberCard > 3)
    {
        if (this->buttons.find("RIGHT") == this->buttons.end())
        {
            this->buttons["RIGHT"] = new gui::Button
            (
                this->window.getPosition().x + this->window.getSize().x - 63.f,
                this->window.getPosition().y + this->window.getSize().y - 40.f,
                30.f, 30.f,
                &this->aotFont, ">", 40, false,
                sf::Color::Red, sf::Color::Red, sf::Color::Red,
                sf::Color::White, sf::Color::Yellow, sf::Color::Black,
                sf::Color::Red, sf::Color::Red, sf::Color::Red
            );
        }

        if (this->buttons.find("LEFT") == this->buttons.end())
        {
            this->buttons["LEFT"] = new gui::Button
            (
                this->window.getPosition().x + 10.f,
                this->window.getPosition().y + this->window.getSize().y - 40.f,
                30.f, 30.f,
                &this->aotFont, "<", 40, false,
                sf::Color::Red, sf::Color::Red, sf::Color::Red,
                sf::Color::White, sf::Color::Yellow, sf::Color::Black,
                sf::Color::Red, sf::Color::Red, sf::Color::Red
            );
        }

        if (this->buttons["RIGHT"]->isReleased())
        {
            auto first = std::move(this->inventoryCards[0]);

            for (int i = 0; i < this->numberCard - 1; i++)
            {
                this->inventoryCards[i] = std::move(this->inventoryCards[i + 1]);
            }

            this->inventoryCards.back() = std::move(first);

        }

        if (this->buttons["LEFT"]->isReleased())
        {
            auto last = std::move(this->inventoryCards[this->numberCard - 1]);

            for (int i = this->numberCard - 1; i > 0; i--)
            {
                this->inventoryCards[i] = std::move(this->inventoryCards[i - 1]);
            }

            this->inventoryCards[0] = std::move(last);
        }
    }

    if (this->buttons["USE_SKILL"]->isReleased())
    {
        //логика для скилла
        this->showWindow = false;
    } 

    if(!this->inventoryCards.empty())
    {

        bool card_used = false;
    
        auto new_end = std::remove_if
        (
            inventoryCards.begin(), inventoryCards.end(), 
            [&](const std::unique_ptr<gui::WarehouseCard>& card)
            {
                if (card && card->isHover() && this->buttons["USE_CARD"]->isReleased())
                {
                    this->showWindow = false;
                    card_used = true;
                    return true;
                }
                return false;
            }
        );
    
        if (card_used) 
        {
            inventoryCards.erase(new_end, inventoryCards.end());
            this->numberCard = inventoryCards.size();
        }
    }
}

void gui::PlayerWindow::renderCards(sf::RenderTarget &target)
{
    int condition;
    if (!this->inventoryCards.empty())
    {   
        if (this->inventoryCards.size() > 2) condition = 3;
        else condition = this->inventoryCards.size();

        for (int i = 0; i < condition; i++)
        {
            if (this->inventoryCards[i] != NULL)
            {
                this->inventoryCards[i]->render(target);
            }
        }
    }

}

void gui::PlayerWindow::renderButtons(sf::RenderTarget &target)
{
    this->buttons["USE_SKILL"]->render(target);
    this->buttons["USE_CARD"]->render(target);

    if (this->numberCard > 3)
    {
        this->buttons["RIGHT"]->render(target);
        this->buttons["LEFT"]->render(target);
    }

}

void gui::PlayerWindow::render(sf::RenderTarget *target)
{
    target->draw(this->window);
    target->draw(this->windowBackground);
    target->draw(this->titleText);
    target->draw(this->icon);
    target->draw(this->infoText);
    target->draw(this->descriptionText);
    target->draw(this->passiveSkillNameText);
    target->draw(this->passiveSkillDescriptionText);
    target->draw(this->activeSkillNameText);
    target->draw(this->activeSkillDescriptionText);
    target->draw(this->inventoryText);

    if(!this->healthLine.empty())
    {
        for(int i = 0; i < this->player.getHealth(); i++)
        {
            target->draw(this->healthLine[i]);
        }
    }
    
    this->renderButtons(*target);
    this->renderCards(*target);
}

/*------------------------------------CLASS BEAST WINDOW----------------------------------------------*/

void gui::BeastWindow::initText()
{
    this->beastTitle = "Oh sheet!";
    this->beastInfo = "He Attack!";

    this->congratulationTitle = "Congratulations!";
    this->congratulationInfo = "You great!";

    this->breakHeardTitle = "Oh no!";
    this->breakHeardInfo = "Head shot!";

    this->infoText.setCharacterSize(32);
    this->titleText.setCharacterSize(40);

    this->infoText.setFont(this->font);
    this->titleText.setFont(this->font);
}

void gui::BeastWindow::initTexture()
{
    this->bestColor = sf::Color::Blue;
    this->congratulationColor = sf::Color::Red;
    this->breakHeardColor = sf::Color::Black;
}

void gui::BeastWindow::initBackground()
{
    this->windowBackground.setSize
    (
        this->window.getSize()
    );

    this->windowBackground.setPosition
    (
        this->window.getPosition()
    );

    this->windowBackground.setFillColor(sf::Color(160, 82, 45));
    this->windowBackground.setOutlineColor(sf::Color::Black);
    this->windowBackground.setOutlineThickness(3);
}

void gui::BeastWindow::initWindow()
{
    this->window.setSize(this->sizeWindow);
    this->window.setPosition(this->positionWindow);
    this->window.setFillColor(sf::Color::Black);
}

void gui::BeastWindow::initButtons()
{
    this->buttons["OK"] = new gui::Button
    (
        this->window.getPosition().x + this->window.getSize().x / 2.f - 63.f,
        this->window.getPosition().y + this->window.getSize().y - 70.f,
        90.f, 45.f,
        &this->aotFont, "OK", 20, true,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );
}

void gui::BeastWindow::initVariables()
{
    this->fate = 3;
    this->state = BeastWindowState::BW_BEAST;
    this->showWindow = true;
}

void gui::BeastWindow::initIcon()
{
    this->iconShape.setSize
    (
        sf::Vector2f
        (
            this->window.getSize().x / 12.f * 4.f, 
            this->window.getSize().y / 12.f * 3.f
        )
    );

    this->iconShape.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + this->window.getSize().x / 2.f - this->iconShape.getSize().x / 2.f,
            this->window.getPosition().y + this->window.getSize().y / 2.f - this->iconShape.getSize().y / 2.f
        )
    );
}

gui::BeastWindow::BeastWindow(sf::Vector2f position_window, sf::Vector2f size_window) : InteractiveWindow()
{
    this->positionWindow = position_window;
    this->sizeWindow = size_window;

    this->initVariables();
    this->initWindow();
    this->initTexture();
    this->initText();
    this->initBackground();
    this->initIcon();
    this->initButtons();
}

gui::BeastWindow::~BeastWindow()
{
}


void gui::BeastWindow::updateButtons(const float &dt, const sf::Vector2i &mouse_pos_window)
{
    for (auto& it : this->buttons)
    {
        it.second->update(mouse_pos_window, dt);
    }

    if (this->state == BeastWindowState::BW_BREAK_HEART || this->state == BeastWindowState::BW_CONGRATULATION)
    {
        this->buttons["OK"]->setLock(false);
    }

    if (this->buttons["OK"]->isReleased() && this->state != BeastWindowState::BW_BEAST)
    {
        this->showWindow = false;
    }
}

void gui::BeastWindow::updateElapsedTime()
{
}

void gui::BeastWindow::updateText()
{
    switch (state)
    {
    case BeastWindowState::BW_BEAST:
        this->title = this->beastTitle;
        this->info = this->beastInfo;
        break;

    case BeastWindowState::BW_CONGRATULATION:
        this->title = this->congratulationTitle;
        this->info = this->congratulationInfo;
        break;
    
    case BeastWindowState::BW_BREAK_HEART:
        this->title = this->breakHeardTitle;
        this->info = this->breakHeardInfo;
        break;
    
    default:
        std::cout<<"Error in BeastWindow::updateText"<<std::endl;
        break;
    }

    this->titleText.setString(this->title);
    this->infoText.setString(this->info);

    this->titleText.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + this->window.getSize().x / 2.f - this->titleText.getGlobalBounds().width / 2.f,
            this->window.getPosition().y + 2.f
        )
    );

    this->infoText.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + this->window.getSize().x / 2.f - this->infoText.getGlobalBounds().width / 2.f,
            this->titleText.getPosition().y + this->titleText.getGlobalBounds().height + 50.f
        )
    );
}

void gui::BeastWindow::updateIcon()
{
    switch (state)
    {
    case BeastWindowState::BW_BEAST:
        this->iconShape.setFillColor(this->bestColor);
        break;

    case BeastWindowState::BW_CONGRATULATION:
        this->iconShape.setFillColor(this->congratulationColor);
        break;
    
    case BeastWindowState::BW_BREAK_HEART:
        this->iconShape.setFillColor(this->breakHeardColor);
        break;
    
    default:
        std::cout<<"Error in BeastWindow::updateIcon"<<std::endl;
        break;
    }
}

void gui::BeastWindow::update(const float &dt, const sf::Vector2i &mouse_pos_window, int& dice_result)
{
    if (dice_result == 0)
    {
        this->state = BeastWindowState::BW_BEAST;
    }
    else if (dice_result >= this->fate)
    {
        this->state = BeastWindowState::BW_CONGRATULATION;
    }
    else
    {
        this->state = BeastWindowState::BW_BREAK_HEART;
    }

    this->updateIcon();
    this->updateText();
    this->updateButtons(dt, mouse_pos_window);
}

void gui::BeastWindow::renderButtons(sf::RenderTarget &target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void gui::BeastWindow::render(sf::RenderTarget *target)
{
    target->draw(this->window);
    target->draw(this->windowBackground);
    target->draw(this->titleText);
    target->draw(this->infoText);
    target->draw(this->iconShape);
    this->renderButtons(*target);
}


/*------------------------------------CLASS Battle WINDOW----------------------------------------------*/

void gui::BattleWindow::initTexture()
{
    this->titanIconColor = sf::Color::Red;
    this->playerIconColor = sf::Color::Blue;
}

void gui::BattleWindow::initBackground()
{
     this->windowBackground.setSize
    (
        this->window.getSize()
    );

    this->windowBackground.setPosition
    (
        this->window.getPosition()
    );

    this->windowBackground.setFillColor(sf::Color(160, 82, 45));
    this->windowBackground.setOutlineColor(sf::Color::Black);
    this->windowBackground.setOutlineThickness(3);
}

void gui::BattleWindow::initVariables()
{
    this->showWindow = true;
    this->delay = false;
    this->needThrow = 0;
    this->iconSize = sf::Vector2f(150.f, 300.f);
    this->isSetPositionIcons = false;
}

void gui::BattleWindow::initWindow()
{
    this->window.setSize(this->sizeWindow);
    this->window.setPosition(this->positionWindow);
    this->window.setFillColor(sf::Color::Black);
}

void gui::BattleWindow::initText()
{
    this->startTitle = "Battle with the Titan";
    this->startInfo = "Press Start button";
    
    this->playerTurnTitle = "Player's turn";

    this->titanTurnTitle = "Titan's turn";

    this->playerWonTitle = "Congratulations!";
    this->playerWonInfo = "You win";

    this->titanWonTitle = "Oh, no";
    this->titanWonInfo = "You lose";

    this->titleText.setCharacterSize(40);
    this->infoText.setCharacterSize(32);
    this->needThrowText.setCharacterSize(32);
    this->diceResultText.setCharacterSize(32);
    this->playerNameText.setCharacterSize(30);
    this->titanNameText.setCharacterSize(30);

    this->titleText.setFont(this->aotFont);
    this->infoText.setFont(this->aotFont);
    this->needThrowText.setFont(this->font);
    this->diceResultText.setFont(this->font);
    this->playerNameText.setFont(this->aotFont);
    this->titanNameText.setFont(this->aotFont);
}

void gui::BattleWindow::initButtons()
{
    this->buttons["OK"] = new gui::Button
    (
        this->window.getPosition().x + this->window.getSize().x / 2.f - 63.f,
        this->window.getPosition().y + this->window.getSize().y - 70.f,
        90.f, 45.f,
        &this->aotFont, "OK", 20, false,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );

    this->buttons["START"] = new gui::Button
    (
        this->window.getPosition().x + this->window.getSize().x / 2.f - 63.f,
        this->window.getPosition().y + this->window.getSize().y - 70.f,
        90.f, 45.f,
        &this->aotFont, "Start", 20, false,
        sf::Color::Red, sf::Color::Red, sf::Color::Red,
        sf::Color::White, sf::Color::Yellow, sf::Color::Black,
        sf::Color::Red, sf::Color::Red, sf::Color::Red
    );
}

void gui::BattleWindow::initIcon()
{
    this->playerIcon.setSize(this->iconSize);
    this->titanIcon.setSize(this->iconSize);

    this->playerIcon.setFillColor(this->playerIconColor);
    this->titanIcon.setFillColor(this->titanIconColor);
}

gui::BattleWindow::BattleWindow
(
    sf::Vector2f position_window, sf::Vector2f size_window, 
    Player& player, Titan& titan, BattleState& state
) 
  : InteractiveWindow(),
    initPlayerAndTitanHealthLine(false), initPlayerAndTitanName(false), isSetPositionIcons(false), delay(false),
    player(player), titan(titan), state(state)
{
    this->positionWindow = position_window;
    this->sizeWindow = size_window;

    this->initVariables();
    this->initTexture();
    this->initIcon();
    this->initWindow();
    this->initText();
    this->initBackground();
    this->initButtons();
}

gui::BattleWindow::~BattleWindow()
{
}


void gui::BattleWindow::updateText(std::string dice_result, bool apply_changes)
{
    switch (this->state)
    {
    case Start:
        this->titleText.setString(this->startTitle);
        this->infoText.setString(this->startInfo);    
        break;

    case PlayerTurn:
        this->needThrowString = std::to_string(this->needThrow);
        this->needThrowText.setString(this->needThrowString);

        this->playerTurnInfo = "To attack, roll a die greater than ";
        this->titleText.setString(this->playerTurnTitle);
        this->infoText.setString(this->playerTurnInfo);    
        break;
    
    case TitanTurn:
        this->needThrowString = std::to_string(this->needThrow);
        this->needThrowText.setString(this->needThrowString);

        this->titanTurnInfo = "To defend, roll a die greater than ";
        this->titleText.setString(this->titanTurnTitle);
        this->infoText.setString(this->titanTurnInfo);    
        break;

    case PlayerWon:
        this->titleText.setString(this->playerWonTitle);
        this->infoText.setString(this->playerWonInfo);
        break;
    
    case TitanWon:
        this->titleText.setString(this->titanWonTitle);
        this->infoText.setString(this->titanWonInfo);
    
    default:
        std::cerr<<"Error in TitanWindow::updateText"<<std::endl;
        break;
    }

    this->titleText.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + this->window.getSize().x / 2.f - this->titleText.getGlobalBounds().width / 2.f,
            this->window.getPosition().y + 5.f
        )
    );

    this->infoText.setPosition
    (
        sf::Vector2f
        (
            this->window.getPosition().x + this->window.getSize().x / 2.f - this->infoText.getGlobalBounds().width / 2.f,
            this->titleText.getPosition().y + this->titleText.getGlobalBounds().height + 10.f
        )
    );

    if (this->state != Start)
    {
        if (!this->initPlayerAndTitanName)
        {
            this->titanNameString = this->titan.getName();
            this->playerNameString = this->player.getName();

            this->titanNameText.setString(this->titanNameString);
            this->playerNameText.setString(this->playerNameString);

            this->playerNameText.setCharacterSize(35);
            this->titanNameText.setCharacterSize(35);

            this->playerNameText.setPosition
            (
                sf::Vector2f
                (
                    this->window.getPosition().x + this->window.getSize().x / 3.f - this->playerNameText.getGlobalBounds().width / 2.f - 150.f,
                    this->window.getPosition().y + 2.f
                )
            );

            this->titanNameText.setPosition
            (
                sf::Vector2f
                (
                    this->window.getPosition().x + this->window.getSize().x / 3.f * 2.f - this->titanNameText.getGlobalBounds().width / 2.f + 150.f,
                    this->window.getPosition().y + 2.f
                )
            );

            switch (this->titan.getType())
            {
            case SLOW:
                this->needThrow = 3;
                break;

            case ORDINARY:
                this->needThrow = 4;
                break;

            case ANOMALOUS:
                this->needThrow = 5;
                break;
            
            default:
                break;
            }
            initPlayerAndTitanName = true;
        }
        
        if (this->state == PlayerTurn || this->state == TitanTurn)
          {
              this->needThrowText.setPosition
              (
                  sf::Vector2f
                  (
                      this->infoText.getPosition().x + this->infoText.getGlobalBounds().width,
                      this->infoText.getPosition().y
                  )
              );

              this->diceResult = "Dice Result: " + dice_result;
              this->diceResultText.setString(this->diceResult);
              this->diceResultText.setPosition
              (
                  sf::Vector2f
                  (
                      this->window.getPosition().x + this->window.getSize().x / 2.f - this->diceResultText.getGlobalBounds().width,
                      this->window.getPosition().y + this->window.getSize().y - 70.f
                  )
              );
          }
    }
}

void gui::BattleWindow::updateIcon(bool apply_changes)
{
    if (!this->isSetPositionIcons && this->state != Start)
    {
        float player_x = this->window.getPosition().x + this->window.getSize().x / 3.f - this->iconSize.x / 2.f;
        float titan_x = this->window.getPosition().x + this->window.getSize().x / 3.f * 2.f - this->iconSize.x / 2.f;
        float y_position = this->window.getPosition().y + this->window.getSize().y / 2.f - this->iconSize.y / 2.f;

        this->playerIcon.setPosition(player_x, y_position);
        this->titanIcon.setPosition(titan_x, y_position);
        
        this->isSetPositionIcons = true;
    }

    if (apply_changes || !this->delay)
    {
        if (this->state == PlayerTurn)
        {
            this->playerIcon.setSize
            (
                sf::Vector2f
                (
                    this->iconSize.x * 1.2,
                    this->iconSize.y * 1.2
                )
            );
    
            this->titanIcon.setSize
            (
                sf::Vector2f
                (
                    this->iconSize.x,
                    this->iconSize.y
                )
            );
        }
    
        else if (this->state == TitanTurn)
        {
            this->titanIcon.setSize
            (
                sf::Vector2f
                (
                    this->iconSize.x * 1.2,
                    this->iconSize.y * 1.2
                )
            );
    
            this->playerIcon.setSize
            (
                sf::Vector2f
                (
                    this->iconSize.x,
                    this->iconSize.y
                )
            );
        }
    
        else 
        {
            this->titanIcon.setSize
            (
                sf::Vector2f
                (
                    this->iconSize.x,
                    this->iconSize.y
                )
            );
    
            this->playerIcon.setSize
            (
                sf::Vector2f
                (
                    this->iconSize.x,
                    this->iconSize.y
                )
            );
        }

        if (!this->delay)
        {
            this->delay = true;
        }
    }
    
}

void gui::BattleWindow::updateHealthLines()
{
    if (this->state != Start)
    {
        if (!this->initPlayerAndTitanHealthLine && this->initPlayerAndTitanName)
        {
            switch (this->player.getHealth())
            {
            case 4:
                this->player.setPositionHealthLine
                (
                    sf::Vector2f
                    (
                        this->playerNameText.getPosition().x + this->playerNameText.getGlobalBounds().width / 2.f - 100.f,
                        this->playerNameText.getPosition().y + 50.f
                    )
                );
                break;

            case 3:
                this->player.setPositionHealthLine
                (
                    sf::Vector2f
                    (
                        this->playerNameText.getPosition().x + this->playerNameText.getGlobalBounds().width / 2.f - 75.f,
                        this->playerNameText.getPosition().y + 50.f
                    )
                );
                break;

            case 2:
                this->player.setPositionHealthLine
                (
                    sf::Vector2f
                    (
                        this->playerNameText.getPosition().x + this->playerNameText.getGlobalBounds().width / 2.f - 50.f,
                        this->playerNameText.getPosition().y + 50.f
                    )
                );
                break;

            case 1:
                this->player.setPositionHealthLine
                (
                    sf::Vector2f
                    (
                        this->playerNameText.getPosition().x + this->playerNameText.getGlobalBounds().width / 2.f - 25.f,
                        this->playerNameText.getPosition().y + 50.f
                    )
                );
                break;
            
            default:
                std::cerr<<"Error on TitanWindow::updateHealthLines"<<std::endl;
                break;
            }

            switch (this->titan.getHealth())
            {
            case 1:
                this->titan.setPositionHealthLine
                (
                    sf::Vector2f
                    (
                        this->titanNameText.getPosition().x + this->titanNameText.getGlobalBounds().width / 2.f - 25.f,
                        this->titanNameText.getPosition().y + 50.f
                    )
                );
                break;

            case 2:
                this->titan.setPositionHealthLine
                (
                    sf::Vector2f
                    (
                        this->titanNameText.getPosition().x + this->titanNameText.getGlobalBounds().width / 2.f - 50.f,
                        this->titanNameText.getPosition().y + 50.f
                    )
                );
                break;
            
            case 3:
                this->titan.setPositionHealthLine
                (
                    sf::Vector2f
                    (
                        this->titanNameText.getPosition().x + this->titanNameText.getGlobalBounds().width / 2.f - 75.f,
                        this->titanNameText.getPosition().y + 50.f
                    )
                );
                break;
            
            default:
                std::cerr<<"Error on TitanWindow::updateHealthLines"<<std::endl;
                break;
            }
            
            this->initPlayerAndTitanHealthLine = true;
        }
    }
}

void gui::BattleWindow::updateButtons(const float &dt, const sf::Vector2i &mouse_pos_window)
{
    for (auto& it: buttons)
    {
        it.second->update(mouse_pos_window, dt);
    }
    if (this->state == PlayerWon || this->state == TitanWon)
    {        
        if (this->buttons["OK"]->isReleased())
        {
            this->showWindow = false;
        }
    }

    else if (this->state == Start)
    {
        if (this->buttons["START"]->isReleased())
        {
            this->state = PlayerTurn;
        }
    }
}

// void gui::BattleWindow::updateElapsedTime()
// {
//     this->elapsedTime = timer.getElapsedTime().asSeconds();
//
//     if (this->elapsedTime == 3.0f)
//     {
//         this->endTimer = true;
//     }
// }

void gui::BattleWindow::update(const float &dt, const sf::Vector2i &mouse_pos_window, std::string dice_result, bool dice_button_pressed)
{
    if (dice_button_pressed && !this->diceButtonWasPressed && this->delay)
    {
        this->timer.restart();
        this->waitingForDelay = true;
        this->diceButtonWasPressed = true;
    }

    else if (!dice_button_pressed)
    {
        this->diceButtonWasPressed = false;
    }
    
    bool apply_changes = false;
    
    if (this->waitingForDelay && this->timer.getElapsedTime().asSeconds() >= 2.0f)
    {
        apply_changes = true;
        this->waitingForDelay = false;
    }

    this->updateText(dice_result, apply_changes);
    this->updateHealthLines();
    this->updateIcon(apply_changes);
    this->updateButtons(dt, mouse_pos_window);
}


void gui::BattleWindow::renderHealthLine(sf::RenderTarget& target)
{
    this->player.renderHealthLine(target);
    this->titan.renderHealthLine(target);
}

void gui::BattleWindow::renderButtons(sf::RenderTarget &target)
{
    if (this->state == Start)
    {
        this->buttons["START"]->render(target);
    }
    else if (this->state == PlayerWon || this->state == TitanWon)
    {
        this->buttons["OK"]->render(target);
    }
}

void gui::BattleWindow::render(sf::RenderTarget *target)
{
    target->draw(this->window);
    target->draw(this->windowBackground);
    this->renderButtons(*target);    

    target->draw(this->titleText);
    target->draw(this->infoText);
    
    if (this->state != Start)
    {
        if (this->state == PlayerTurn || this->state == TitanTurn)
        {
            target->draw(this->needThrowText);
            target->draw(this->playerNameText);
            target->draw(this->titanNameText);

            target->draw(this->diceResultText);
            
            // if (!this->delay)
            // {   
            //     target->draw(this->playerIcon);
            //     target->draw(this->titanIcon);
            //     this->renderHealthLine(*target);
//
            //     this->delay = true;
//
            //     this->renders =
            //     {
            //         [this](sf::RenderTarget* target) { target->draw(this->playerIcon); },
            //         [this](sf::RenderTarget* target) { target->draw(this->titanIcon); },
            //         [this](sf::RenderTarget* target) { this->renderHealthLine(*target); }
            //     };
            // }
            // else
            // {
            //     this->delayCallRender(target, 3000);
            // }
            
            target->draw(this->playerIcon);
            target->draw(this->titanIcon);
            this->renderHealthLine(*target);

        }
    }
}   

