#ifndef WAREHOUSE_COMPONENT_H
#define WAREHOUSE_COMPONENT_H

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class WarehouseCardDrop;

namespace gui
{
    class Button;
    class WarehouseCard;
}

class WarehouseComponent
{
private:
    std::unique_ptr<WarehouseCardDrop> warehouseCardDrop;
    std::unique_ptr<gui::WarehouseCard> warehouseCard;

    bool activeWarehouse;
    bool wasThrow;

public:
    WarehouseComponent();
    ~WarehouseComponent();

    void startWarehouse(sf::Text& stage_text);
    bool isWarehouseActive() const;

    std::unique_ptr<gui::WarehouseCard> getSelectCard();
    bool getCanGetSelectCard() const;

    void update(const float& dt, const sf::Vector2i& mouse_pos_window, sf::Text& stage_text, sf::Text& dice_result, gui::Button& dice_button);
    void render(sf::RenderTarget* target);
};

#endif // !WAREHOUSE_COMPONENT_H