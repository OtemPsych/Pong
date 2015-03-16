#ifndef Paddle_H_
#define Paddle_H_

#include "Entity.h"
#include "Ball.h"

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
    struct {
        bool UP,
             DOWN;
    } mMovement;

public:
// Constructor
    Paddle(const Side& side,
           const Type& type, const sf::Vector2f& bounds);
// Public Methods
    const void handleAI(Ball& ball);
    const void checkCollision();
    virtual const void update(const sf::Time& dt);

    inline const sf::RectangleShape& getShape() { return mShape; }
};
#endif // Paddle_H_
