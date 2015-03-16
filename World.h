#ifndef World_H_
#define World_H_

#include "Paddle.h"
#include "Ball.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>

class World :private sf::NonCopyable
{
private:
// Private Data Members
    Paddle mPaddle1;
    Paddle mPaddle2;
    Ball   mBall;

    sf::RectangleShape line;

    sf::Font mFont;

    sf::RenderWindow& mWindow;

public:
// Constructor
    explicit World(sf::RenderWindow& window);
// Public Methods
    const void update(const sf::Time& dt);
    const void handleInput(const sf::Keyboard::Key& key, const bool isPressed);
    const void handleAI();
    const void handleCollision();
    const void draw();
};
#endif // World_H_
