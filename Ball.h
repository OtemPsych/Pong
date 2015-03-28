#ifndef Ball_H_
#define Ball_H_

#include "Paddle.h"

#include <SFML/Graphics/CircleShape.hpp>

class Paddle;
class Ball :public Entity
{
private:
// Private Data Member
    sf::CircleShape mShape;
    bool checkCollision;
// Private Method
    const void resetDirection();

public:
// Constructor
    Ball(const Type& type, const sf::Vector2f& bounds);
// Public Methods
    const void handleCollision(Paddle& paddle1, Paddle& paddle2, const bool actualBall);
    virtual const void update(const sf::Time& dt);
    const void resetBall();

    inline sf::CircleShape& getShape() { return mShape; }
    inline const bool getCollisionCheck() { return checkCollision; }
};
#endif // Ball_H_
