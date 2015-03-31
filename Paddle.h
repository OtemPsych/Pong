#ifndef Paddle_H_
#define Paddle_H_

#include "Entity.h"
#include "Ball.h"
#include "TextHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Ball;
class Paddle :public Entity
{
public:
    enum Side { LEFT, RIGHT };
private:
// Private Data Members
    sf::RectangleShape mShape;
    Side               mSide;
    struct movement{
        bool UP,
             DOWN;
    }                  mMovement;
    int                mScore;

public:
// Constructor
    Paddle(const Side& side, const Type& type,
           const sf::Vector2f& bounds);
// Public Methods
    const void handleAI(Ball& ball, Ball& futureBall, const int futureBallMultiplier, const sf::Time& dt);
    const void handleCollision();
    virtual const void update(const sf::Time& dt);
    const void updateScoreText(sf::Text& text);
    const void setFont(TextHolder& holder);

    inline const sf::RectangleShape& getShape() { return mShape; }
    inline movement& getMovement() { return mMovement; }

    inline const void increaseScore() { mScore++; }
    inline const int getScore() const { return mScore; }
};
#endif // Paddle_H_
