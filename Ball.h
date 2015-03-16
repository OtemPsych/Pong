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
// Private Method
    const void resetDirection();

public:
// Constructor
    Ball(const Type& type, const sf::Vector2f& bounds);
// Public Method
    virtual const void update(const sf::Time& dt);
    const void checkCollision(Paddle& paddle1, Paddle& paddle2);
    const void resetBall();

    inline const sf::CircleShape& getShape() { return mShape; }
};
#endif // Ball_H_
