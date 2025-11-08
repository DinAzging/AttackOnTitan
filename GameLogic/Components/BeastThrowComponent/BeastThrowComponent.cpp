#include "BeastThrowComponent.h"
#include "../../../Resource File/Gui.h"
#include "../../Battle/BeastThrow.h"
#include "../../../Entities/Player.h"
#include <random>

BeastThrowComponent::BeastThrowComponent(sf::Vector2f position_window, sf::Vector2f size_window)
    : activeBeast(true), wasDiceTrow(false), diceResult(0), beastDamage(1)
{
    this->beastThrow = std::make_unique<BeastThrow>(position_window, size_window);
}

BeastThrowComponent::~BeastThrowComponent()
{
}

bool BeastThrowComponent::isActiveBeast() const
{
    return this->activeBeast;
}

void BeastThrowComponent::update(const float &dt, const sf::Vector2i &mouse_pos_window, Player &player, gui::Button &dice_btn)
{
    if (!this->wasDiceTrow)
    {
        dice_btn.setLock(false);

        if (dice_btn.isReleased())
        {
            this->wasDiceTrow = true;
            dice_btn.setLock(true);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distribution(1, 6);
            this->diceResult = distribution(gen);

            if (diceResult < 3 && diceResult > 0)
            {
                player.setHealth(player.getHealth() - this->beastDamage);
            }
            
        }
    }

    if (this->beastThrow)
    {
        this->beastThrow->update(dt, mouse_pos_window, this->diceResult);
        this->activeBeast = this->beastThrow->isWindowActive();
    }
}

void BeastThrowComponent::render(sf::RenderTarget *target)
{
    if (this->beastThrow && this->activeBeast)
    {
        this->beastThrow->render(target);
    }
}
