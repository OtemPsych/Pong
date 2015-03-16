#ifndef Game_H_
#define Game_H_

#include "World.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game :private sf::NonCopyable
{
private:
// Private Data Member
    sf::RenderWindow mWindow;
    World            mWorld;
// Private Methods
    const void processEvents();
    const void update(const sf::Time& dt);
    const void handleInput(const sf::Keyboard::Key& key, const bool isPressed);
    const void render();

public:
// Constructor
    Game();
// Public Methods
    const void run();
};
#endif // Game_H_
