#ifndef VIEW_COMPONENT_H
#define VIEW_COMPONENT_H

#include <SFML/Graphics.hpp>

class ViewComponent
{
private:
    sf::View& gameView;
    sf::View defaultView;
    sf::FloatRect viewBounds;
    float moveSpeed;

public:
    ViewComponent(sf::View& view, const sf::View& defaultView);
    ~ViewComponent();

    void clampView();
    void resetToDefault();
    
    void setViewBounds(const sf::FloatRect& bounds);

    void update(const std::map<std::string, int>& keybinds, bool keytime);
};
#endif 