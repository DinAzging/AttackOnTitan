#include "ViewComponent.h"

ViewComponent::ViewComponent(sf::View &view, const sf::View &default_view)
    : gameView(view), defaultView(default_view), moveSpeed(5.f) {}

    ViewComponent::~ViewComponent()
{
}

void ViewComponent::update(const std::map<std::string, int> &keybinds, bool keytime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("VIEW_MOVE_LEFT")))) 
    {
        this->gameView.move(-moveSpeed, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("VIEW_MOVE_UP")))) 
    {
        this->gameView.move(0.f, -moveSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("VIEW_MOVE_DOWN")))) 
    {
        this->gameView.move(0.f, moveSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("VIEW_MOVE_RIGHT")))) 
    {
        this->gameView.move(moveSpeed, 0.f);
    }

    // Ограничение границ
    this->clampView();

    // Сброс к виду по умолчанию
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("DEFAULT_VIEW"))) && keytime) 
    {
        this->resetToDefault();
    }
}

void ViewComponent::clampView()
{
    if (this->viewBounds.width == 0 || this->viewBounds.height == 0) return;

    sf::Vector2f center = this->gameView.getCenter();
    sf::Vector2f size = this->gameView.getSize();

    float min_x = this->viewBounds.left + size.x / 2;
    float max_x = this->viewBounds.left + this->viewBounds.width - size.x / 2;
    float min_y = this->viewBounds.top + size.y / 2;
    float max_y = this->viewBounds.top + this->viewBounds.height - size.y / 2;

    if (center.x < min_x) center.x = min_x;
    if (center.x > max_x) center.x = max_x;
    if (center.y < min_y) center.y = min_y;
    if (center.y > max_y) center.y = max_y;

    this->gameView.setCenter(center);
}

void ViewComponent::resetToDefault()
{
    this->gameView = this->defaultView;
    this->clampView();
}

void ViewComponent::setViewBounds(const sf::FloatRect &bounds)
{
    this->viewBounds = bounds;
    this->clampView();
}
