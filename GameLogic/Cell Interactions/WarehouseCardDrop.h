#ifndef WAREHOUSE_CARD_DROP_H
#define WAREHOUSE_CARD_DROP_H

#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>

namespace gui
{
    class WarehouseCard;
    class WarehouseInteractiveWindow;
}

class WarehouseCardDrop
{   
public:
    enum WarehouseItem
    {
        NOTHING = 0,
        STALL,
        AMMUNITION,
        MEDICINE_CHEST
    };

    WarehouseCardDrop(int dice_result);
    ~WarehouseCardDrop();

    void initWindow(int number_card);

    std::unique_ptr<gui::WarehouseCard> getSelectedCard();
    void setSelectedCard(std::unique_ptr<gui::WarehouseCard> card);

    bool isCanGetSelectCard() const;
    bool isWindowActive() const;

    void update(const float& dt, const sf::Vector2i &mouse_pos_window);
    void render(sf::RenderTarget* target);

private:
    std::unique_ptr<gui::WarehouseInteractiveWindow> window;
    std::unique_ptr<gui::WarehouseCard> choiceCard;

    bool canGetSelectCard;
    bool windowActive;

    WarehouseItem item;
};


#endif // !WAREHOUSE_H
