#include "BeastThrow.h"
#include "../../Resource File/Gui.h"

BeastThrow::BeastThrow(sf::Vector2f position_window, sf::Vector2f size_window)
    : windowActive(true)
{
    this->window = std::make_unique<gui::BeastWindow>(position_window, size_window);
}

BeastThrow::~BeastThrow()
{
}

bool BeastThrow::isWindowActive() const
{
    return this->windowActive;
}

void BeastThrow::update(const float &dt, const sf::Vector2i &mouse_pos_window, int& dice_result)
{
    if (this->window)
    {
        this->window->update(dt, mouse_pos_window, dice_result);
        this->windowActive = this->window->isShowWindow();
    }
}

void BeastThrow::render(sf::RenderTarget *target)
{
    if (this->window)
    {
        if (this->windowActive)
        {
            this->window->render(target);
        }
    }
}
