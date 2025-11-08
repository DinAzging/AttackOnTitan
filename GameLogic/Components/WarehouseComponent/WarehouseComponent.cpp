#include "WarehouseComponent.h"
#include "../../../Resource File/Gui.h"
#include "../../Cell Interactions/WarehouseCardDrop.h"
#include <random>
#include <iostream>

WarehouseComponent::WarehouseComponent()
    : activeWarehouse(false), wasThrow(false)
{
}

WarehouseComponent::~WarehouseComponent()
{
}

void WarehouseComponent::startWarehouse(sf::Text& stage_text)
{
    stage_text.setString("Press DICE!");

    this->activeWarehouse = true;
}

bool WarehouseComponent::isWarehouseActive() const
{
    return this->activeWarehouse;
}

std::unique_ptr<gui::WarehouseCard> WarehouseComponent::getSelectCard()
{
    if (this->warehouseCardDrop->isCanGetSelectCard())
    {
        return std::move(this->warehouseCardDrop->getSelectedCard());
    }
    throw std::runtime_error("Card not found");
}

bool WarehouseComponent::getCanGetSelectCard() const
{
    if (this->warehouseCardDrop)
    {
        return this->warehouseCardDrop->isCanGetSelectCard();
    }
    return false;
}

void WarehouseComponent::update(const float& dt, const sf::Vector2i& mouse_pos_window, sf::Text &stage_text, sf::Text &dice_result, gui::Button &dice_button)
{
    if (!this->wasThrow)
    {
        dice_button.setLock(false);
        
        if (dice_button.isReleased())
        {
            this->wasThrow = true;
            dice_button.setLock(true);

            int result;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distribution(1, 6);
            result = distribution(gen);

            dice_result.setString(std::to_string(result));
            this->warehouseCardDrop = std::make_unique<WarehouseCardDrop>(result);

        }
    }
    if (this->warehouseCardDrop)
    {
        this->warehouseCardDrop->update(dt, mouse_pos_window); 
        this->activeWarehouse = this->warehouseCardDrop->isWindowActive();
    }
}

void WarehouseComponent::render(sf::RenderTarget *target)
{
    if (this->warehouseCardDrop)
    {
        this->warehouseCardDrop->render(target);
    }
}
