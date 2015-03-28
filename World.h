#ifndef World_H_
#define World_H_

#include "Paddle.h"
#include "Ball.h"
#include "TextHolder.h"

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

    Ball   mBallPrediction;
    int    mBallMultiplier;

    sf::RectangleShape line;

    TextHolder&       mTextHolder;
    sf::RenderWindow& mWindow;

public:
// Constructor
    World(TextHolder& holder, sf::RenderWindow& window);
// Public Methods
    const void update(const sf::Time& dt);
    const void handleInput(const sf::Keyboard::Key& key, const bool isPressed);
    const void handleAI(const bool mode, const sf::Time& dt);
    const void handleCollision();
    const void draw();

    const void checkScoreChanges();
    const void resetGame(const sf::Font& font);

    const void setFonts(const sf::Font& font);
};
#endif // World_H_
