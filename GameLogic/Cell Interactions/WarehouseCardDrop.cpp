#include "WarehouseCardDrop.h"
#include "../../Resource File/Gui.h"
#include <iostream>

WarehouseCardDrop::WarehouseCardDrop(int dice_result)
    : canGetSelectCard(false), windowActive(true)
{
    switch (dice_result)
    {
    case 1:
        this->initWindow(0);
        break;

    case 2:
        this->initWindow(1);
        break;
    
    case 3:
        this->initWindow(1);
        break;
    
    case 4:
        this->initWindow(2);
        break;

    case 5:
        this->initWindow(2);

    case 6:
        this->initWindow(3);

    default:
        break;
    }
}

WarehouseCardDrop::~WarehouseCardDrop()
{
}

void WarehouseCardDrop::initWindow(int number_card)
{
    this->window = std::make_unique<gui::WarehouseInteractiveWindow>(number_card, sf::Vector2f(460.f, 130.f), sf::Vector2f(1005.f, 680.f));
}

std::unique_ptr<gui::WarehouseCard> WarehouseCardDrop::getSelectedCard()
{
    if (!this->choiceCard) 
    {
        throw std::runtime_error("No card selected");
    }
    
    this->canGetSelectCard = false;
    return std::move(this->choiceCard);
}

void WarehouseCardDrop::setSelectedCard(std::unique_ptr<gui::WarehouseCard> card)
{
    this->choiceCard = std::move(card);
}

bool WarehouseCardDrop::isCanGetSelectCard() const
{
    return this->canGetSelectCard;
}

bool WarehouseCardDrop::isWindowActive() const
{
    return this->windowActive;
}

void WarehouseCardDrop::update(const float& dt, const sf::Vector2i &mouse_pos_window)
{
    if (this->window)
    {    
        this->window->update(dt, mouse_pos_window);

        if (!this->window->isShowWindow())
        {
            if (!this->window->isCardEmpty())
            {
                this->setSelectedCard(this->window->getSelectCard());
                this->canGetSelectCard = true;

                //мб не нужно
                switch (this->window->getSelectType())
                {
                case WarehouseCardType::STALL:
                    this->item = WarehouseItem::STALL;
                    break;

                case WarehouseCardType::AMMUNITION:
                    this->item = WarehouseItem::AMMUNITION;
                    break;

                case WarehouseCardType::MEDICINE_CHEST:
                    this->item = WarehouseItem::MEDICINE_CHEST;
                    break;
                
                default:
                    break;
                }
            }
            else
            {
                this->item = WarehouseItem::NOTHING;
            }
            this->windowActive = false;
            this->window.reset();
        }
    }
}
void WarehouseCardDrop::render(sf::RenderTarget* target)
{
    if (this->window)
    {
        if (this->window->isShowWindow())
        {
            this->window->render(target);
        }
    }
}



