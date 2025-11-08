#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <memory>
#include <string>

class Player;

class Titan;

enum TitanType : int;

enum BattleState : int;

enum CardState
{
    CARD_IDLE = 0, 
    CARD_HOVER
};

enum WarehouseCardType
    {
        NOTHING = 0,
        STALL,
        AMMUNITION,
        MEDICINE_CHEST
    };

enum ButtonState 
    {
        BTN_IDLE = 0, 
        BTN_HOVER,
        BTN_ACTIVE
    };

enum BeastWindowState
{
    BW_BEAST = 0,
    BW_CONGRATULATION,
    BW_BREAK_HEART
};

// enum TitanWindowState
// {
//     TW_START = 0,
//     TW_PLAYER_TURN,
//     TW_TITAN_TURN,
//     TW_PLAYER_WON,
//     TW_TITAN_WON
// };
 
namespace gui
{
    class Card
    {
    protected:
        sf::RectangleShape shape;
        sf::Texture* shapeTexture; //remove later

        std::string title;
        sf::Text titleText;

        sf::Font font;
        sf::Font AoT_Font;

        sf::Vector2f position;

        CardState cardState;

        float keytime;
        float keytimeMax;

        bool pressing;

        virtual void initVariables() = 0;

    public:
        Card();
        virtual ~Card();

        virtual void setPosition(float posX, float posY) = 0;
        sf::Vector2f getPosition();
        sf::Vector2f getSize();

        CardState getCardState();

        const bool getKeytime();

        const bool checkPressing();

        const bool isHover();
        void dontHover();

        void canPress();
        void cantPress();

        virtual void update(const float& dt, const sf::Vector2i& mouse_pos_window) = 0;
        void updateKeyTime(const float& dt);

        virtual void render(sf::RenderTarget& target) = 0;      
    };

    class PlayerCard : public Card
    {
    private:
        std::string route;
        sf::Text routeText;

        bool gost;

        virtual void initVariables();
        
    public:
        PlayerCard(std::string route);
        PlayerCard(const PlayerCard& other);                // Конструктор копирования
        PlayerCard(PlayerCard&& other) noexcept;            // Конструктор перемещения
        PlayerCard& operator=(const PlayerCard& other);     // Оператор присваивания
        PlayerCard& operator=(PlayerCard&& other) noexcept; // Оператор перемещения
        virtual ~PlayerCard();

        virtual void setPosition(float posX, float posY);

        void swap(PlayerCard& other) noexcept;

        void setGost(bool gost);
        bool getGost();

        std::string getRoute();

        virtual void update(const float& dt, const sf::Vector2i& mouse_pos_window);
        virtual void render(sf::RenderTarget& target);
    };
    
    class WarehouseCard : public Card
    {
    private:
        std::string info;
        sf::Text infoText;

        int index;

        WarehouseCardType type;

        virtual void initVariables();

    public:
        WarehouseCard(WarehouseCardType type);
        WarehouseCard& operator=(const WarehouseCard& other);     // Оператор присваивания
        virtual ~WarehouseCard();

        virtual void setPosition(float posX, float posY);

        void setIndex(int index);
        int getIndex();

        void setWarehouseCardType(WarehouseCardType type);
        WarehouseCardType getWarehouseCardType();

        void useCard();

        virtual void update(const float& dt, const sf::Vector2i& mouse_pos_window);
        virtual void render(sf::RenderTarget& target);
    };
    
    class Deck
    {
    private:
        std::vector<PlayerCard> cards;
    
    public:
        Deck();
        virtual ~Deck(); 

        void addCard(PlayerCard other);

        void shuffle();

        void clear();

        bool isEmpty();

        std::string distribution();
    };

    class TitanDeck
    {
    private:
        std::vector<char> titanDeck;
       
    public:
        TitanDeck();
        virtual ~TitanDeck();

        void addCard(char titanType);

        void shuffle();

        void clear();

        bool isEmpty();

        char getLastType();

        void popType();
    };

    class Button 
    {
    public:
        Button
        (
        float x, float y, float width, float height,
        sf::Font* font, std::string text, unsigned character_size, bool lock,
        sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
        sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
        sf::Color outline_idle_color = sf::Color::Transparent, 
        sf::Color outline_hover_color = sf::Color::Transparent, 
        sf::Color outline_active_color = sf::Color::Transparent
        );

        virtual ~Button();

        //Functions
        const bool isPressed();

        const std::string getText() const;
        const bool getLock() const;
        const bool getKeytime();
        const bool isReleased();

        void updateKeyTime(const float& dt);

        void setText(const std::string text);
        void setLock(const bool lock);

        void update(const sf::Vector2i& mouse_pos_window, const float& dt);
        void render(sf::RenderTarget& target);

    private:
        ButtonState buttonState;
        
        float keytime;
        float keytimeMax;

        bool lock;
        bool isBeingHeld;

        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;
    };

    class InteractiveWindow
    {
    protected:
        sf::RectangleShape window;
        sf::RectangleShape windowBackground; //remove later on texture

        sf::Vector2f positionWindow; //подумоть
        sf::Vector2f sizeWindow; //подумоть

        std::map<std::string, gui::Button*> buttons;

        //std::vector<std::function<void(sf::RenderTarget* target)>> renders;

        sf::Font aotFont;
        sf::Font font;

        std::string title;
        std::string info;
        sf::Text titleText;
        sf::Text infoText;

        bool showWindow;

        sf::Clock timer;
        float elapsedTime;

        //bool endTimer;
        bool diceButtonWasPressed;
        bool waitingForDelay;

        void initFont();
        virtual void initText() = 0;
        virtual void initTexture() = 0;
        virtual void initBackground() = 0;
        virtual void initWindow() = 0;
        virtual void initButtons() = 0;
        virtual void initVariables() = 0; 

    public:
        InteractiveWindow();
        ~InteractiveWindow();

        const bool isShowWindow() const;

        void setShowWindow(bool show);

        sf::Vector2f getSize();

        void deleteButtons();

        virtual void updateButtons(const float& dt, const sf::Vector2i& mouse_pos_window) = 0;
        virtual void renderButtons(sf::RenderTarget& target) = 0;
        virtual void render(sf::RenderTarget* target) = 0;
    };
    
    class WarehouseInteractiveWindow : public InteractiveWindow
    {
    private:
        std::vector<std::unique_ptr<WarehouseCard>> cards;
        int numberCard;

        WarehouseCardType selectType;

        int indexSelectCard;

        bool chose;

        virtual void initText();
        virtual void initTexture();
        virtual void initBackground();
        virtual void initWindow();
        virtual void initButtons();
        virtual void initVariables(); 
        void initCard();

        void setIndexSelectCard(int index);
        int getIndexSelectCard();

    public:
        WarehouseInteractiveWindow(int number_card, sf::Vector2f position_window, sf::Vector2f size_window);
        ~WarehouseInteractiveWindow();

        WarehouseCardType getSelectType();
        std::unique_ptr<WarehouseCard> getSelectCard();
        
        bool isCardEmpty();

        void updateCard(const float& dt, const sf::Vector2i& mouse_pos_window);

        virtual void updateElapsedTime();
        virtual void updateButtons(const float& dt, const sf::Vector2i& mouse_pos_window);

        void update(const float& dt, const sf::Vector2i& mouse_pos_window);
        
        virtual void renderButtons(sf::RenderTarget& target);
        virtual void render(sf::RenderTarget* target);
        void renderCard(sf::RenderTarget& target);
    };

    class PlayerWindow : public InteractiveWindow
    {
    private:
        sf::RectangleShape icon;
        sf::RectangleShape heart;

        sf::Texture iconTexture;
        sf::Texture heartTexture;

        std::string description;
        std::string passiveSkillName;
        std::string passiveSkillDescription;
        std::string activeSkillName;
        std::string activeSkillDescription;
        std::string inventory;

        sf::Text descriptionText;
        sf::Text passiveSkillNameText;
        sf::Text passiveSkillDescriptionText;
        sf::Text activeSkillNameText;
        sf::Text activeSkillDescriptionText;
        sf::Text inventoryText;

        Player& player;
        std::vector <sf::RectangleShape> healthLine;
        std::vector <std::unique_ptr <WarehouseCard> >& inventoryCards;

        int numberCard;

        bool choiceCard;
        bool choiceSkill;

        virtual void initTexture();
        void initIcon();
        virtual void initText();
        virtual void initBackground();
        virtual void initWindow();
        virtual void initButtons();
        virtual void initVariables(); 
        void initInventoryCard();
        void initHealthLine();

    public:
        PlayerWindow(std::vector <std::unique_ptr <WarehouseCard> >&  cards, sf::Vector2f position_window, sf::Vector2f size_window, Player& player);
        ~PlayerWindow();

        void updatePositionCards();

        void updateCards(const float& dt, const sf::Vector2i& mouse_pos_window);
        virtual void updateButtons(const float& dt, const sf::Vector2i& mouse_pos_window);
        virtual void updateElapsedTime();
        void update(const float& dt, const sf::Vector2i& mouse_pos_window);

        void renderCards(sf::RenderTarget& target);
        virtual void renderButtons(sf::RenderTarget& target);
        virtual void render(sf::RenderTarget* target);
    };

    class BeastWindow : public InteractiveWindow
    {
    private:
        sf::RectangleShape iconShape;

        sf::Color bestColor;                //remove to sf::Texture beastTexture
        sf::Color congratulationColor;      //remove to sf::Texture heardTexture
        sf::Color breakHeardColor;          //remove to sf::Texture brakeHeardTexture

        std::string beastTitle;
        std::string beastInfo;

        std::string congratulationTitle;
        std::string congratulationInfo;

        std::string breakHeardTitle;
        std::string breakHeardInfo;

        BeastWindowState state;

        int fate;

        virtual void initText();
        virtual void initTexture();
        virtual void initBackground();
        virtual void initWindow();
        virtual void initButtons();
        virtual void initVariables(); 
        void initIcon();

    public:
        BeastWindow(sf::Vector2f position_window, sf::Vector2f size_window);
        ~BeastWindow();

        virtual void updateButtons(const float& dt, const sf::Vector2i& mouse_pos_window);
        virtual void updateElapsedTime();
        void updateText();
        void updateIcon();
        void update(const float& dt, const sf::Vector2i& mouse_pos_window, int& dice_result);

        virtual void renderButtons(sf::RenderTarget& target);
        virtual void render(sf::RenderTarget* target);
    };

    class BattleWindow : public InteractiveWindow
    {
    private:
        sf::RectangleShape titanIcon;
        sf::RectangleShape playerIcon;
        
        sf::Color titanIconColor;            //remove to sf::Texture titanIconTexture;
        sf::Color playerIconColor;           //remove to sf::Texture playerIconTexture;

        std::string currentTitle;
        std::string currentInfo;
        std::string pendingTitle;
        std::string pendingInfo;

        std::string startTitle;
        std::string startInfo;

        std::string titanTurnTitle;
        std::string titanTurnInfo;

        std::string playerTurnTitle;
        std::string playerTurnInfo;

        std::string titanWonTitle;
        std::string titanWonInfo;

        std::string playerWonTitle;
        std::string playerWonInfo;

        std::string playerNameString;
        sf::Text playerNameText;

        std::string titanNameString;
        sf::Text titanNameText;

        std::string diceResult;
        sf::Text diceResultText;

        int needThrow;
        std::string needThrowString;
        sf::Text needThrowText;

        sf::Vector2f iconSize;

        BattleState& state;

        Player& player;
        Titan& titan;

        bool initPlayerAndTitanName;
        bool initPlayerAndTitanHealthLine;
        bool isSetPositionIcons;
        bool delay;

        virtual void initTexture();
        virtual void initBackground();
        virtual void initVariables(); 
        virtual void initWindow();
        virtual void initText();
        virtual void initButtons();

        void initIcon();
        void initTextPositions();
        void initIconPositions();
        void initHealthLinePositions();
        void initNamesAndThrow();

    public:
        BattleWindow
        (
            sf::Vector2f position_window, sf::Vector2f size_window, 
            Player& player, Titan& titan, BattleState& state
        );
        virtual ~BattleWindow();

        void updateText(std::string dice_result, bool apply_changes);
        void updateIcon(bool apply_changes);
        void updateHealthLines();
        void updateHealthLinePositions();

        virtual void updateButtons(const float& dt, const sf::Vector2i& mouse_pos_window);
        void update(const float &dt, const sf::Vector2i &mouse_pos_window, std::string dice_result = "", bool dice_button_pressed = false);

        void renderHealthLine(sf::RenderTarget& target);
        virtual void renderButtons(sf::RenderTarget& target);
        virtual void render(sf::RenderTarget* target);

    };
};

namespace std 
{
    template <>
    void swap(gui::PlayerCard& a, gui::PlayerCard& b) noexcept;
}
#endif 