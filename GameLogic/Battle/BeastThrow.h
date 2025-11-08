#ifndef BEAST_THROW_H
#define BEAST_THROW_H

#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>

namespace gui
{
    class BeastWindow;
}

class Player;

class BeastThrow
{
private:
    std::unique_ptr<gui::BeastWindow> window;
    
    bool windowActive;
    

public:
    BeastThrow(sf::Vector2f position_window, sf::Vector2f size_window);
    ~BeastThrow();

    bool isWindowActive() const;

    void update(const float &dt, const sf::Vector2i &mouse_pos_window, int& dice_result);
    void render(sf::RenderTarget* target);
};

#endif // !BEAST_THROW_H