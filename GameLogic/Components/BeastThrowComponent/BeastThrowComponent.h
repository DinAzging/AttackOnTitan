#ifndef BEAST_TROW_COMPONENT
#define BEAST_TROW_COMPONENT

#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>

class Player;

namespace gui
{
    class Button;
}

class BeastThrow;

class BeastThrowComponent
{
private:
    std::unique_ptr<BeastThrow> beastThrow;

    bool activeBeast;
    bool wasDiceTrow;

    int beastDamage;

    int diceResult;
public:
    BeastThrowComponent(sf::Vector2f position_window, sf::Vector2f size_window);
    ~BeastThrowComponent();

    bool isActiveBeast() const;

    void update(const float &dt, const sf::Vector2i &mouse_pos_window, Player& player, gui::Button& dice_btn);
    void render(sf::RenderTarget* target);
};

#endif