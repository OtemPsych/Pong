#include "Ball.h"

#include <cstdlib>

// Constructor
Ball::Ball(const Type& type, const sf::Vector2f& bounds)
    : Entity(type, bounds)
    , checkCollision(false)
{
// Set Bounds
    sf::FloatRect shapeBounds = mShape.getLocalBounds();
    mShape.setOrigin(shapeBounds.width / 2, shapeBounds.height / 2);
// Set Size
    mShape.setRadius(5.f);
// Set Position / Velocity
    resetBall();
// Set Color
    mShape.setFillColor(sf::Color::White);
}

// Private Method
    // Reset Velocity
const void Ball::resetDirection()
{
    bool xVelD = rand() % 2;
    bool yVelD = rand() % 2;
    (!xVelD) ? (setVelocity(sf::Vector2f(-getVelocity().x, getVelocity().y)))
             : (setVelocity(sf::Vector2f(-(-getVelocity().x), getVelocity().y)));

    (!yVelD) ? (setVelocity(sf::Vector2f(getVelocity().x, -getVelocity().y)))
             : (setVelocity(sf::Vector2f(getVelocity().x, -(-getVelocity().y))));
}

// Public Methods
   // Check Collision
const void Ball::handleCollision(Paddle& paddle1, Paddle& paddle2, const bool actualBall)
{
// Wall Collision
    if (mShape.getPosition().y < 0.f || mShape.getPosition().y + mShape.getRadius() * 2 > getBounds().y) {
        setVelocity(sf::Vector2f(getVelocity().x, -getVelocity().y));
        checkCollision = true;
    }
    else
        checkCollision = false;

// Paddle Collision
    // Paddle 1
    if (actualBall) {
        if (mShape.getPosition().x < paddle1.getShape().getPosition().x + paddle1.getShape().getSize().x
         && mShape.getPosition().x + mShape.getRadius() * 2 > paddle1.getShape().getPosition().x
         && mShape.getPosition().y < paddle1.getShape().getPosition().y + paddle1.getShape().getSize().y
         && mShape.getPosition().y + mShape.getRadius() * 2 > paddle1.getShape().getPosition().y) {
            setVelocity(sf::Vector2f(-getVelocity().x, getVelocity().y));
            checkCollision = true;
         }

        // Paddle 2
        else if (mShape.getPosition().x + mShape.getRadius() * 2 > paddle2.getShape().getPosition().x
         && mShape.getPosition().x < paddle2.getShape().getPosition().x + paddle2.getShape().getSize().x
         && mShape.getPosition().y < paddle2.getShape().getPosition().y + paddle2.getShape().getSize().y
         && mShape.getPosition().y + mShape.getRadius() * 2 > paddle2.getShape().getPosition().y) {
            setVelocity(sf::Vector2f(-getVelocity().x, getVelocity().y));
            checkCollision = true;
         }
         else
            checkCollision = false;

    // Out of Bounds
        if (mShape.getPosition().x < 0.f) {
            paddle2.increaseScore();
            resetBall();
        }
        else if (mShape.getPosition().x + mShape.getRadius() * 2 > getBounds().x) {
            paddle1.increaseScore();
            resetBall();
        }
    }
    else if (!actualBall) {
        if (mShape.getPosition().x < paddle1.getShape().getPosition().x + paddle1.getShape().getSize().x) {
            setVelocity(sf::Vector2f(0.f, 0.f));
            mShape.setPosition(sf::Vector2f(paddle1.getShape().getPosition().x + paddle1.getShape().getSize().x, mShape.getPosition().y));
        }
        else if (mShape.getPosition().x + mShape.getRadius() * 2 > paddle2.getShape().getPosition().x) {
            setVelocity(sf::Vector2f(0.f, 0.f));
            mShape.setPosition(sf::Vector2f(paddle2.getShape().getPosition().x - mShape.getRadius() * 2, mShape.getPosition().y));
        }
    }
}
    // Update
const void Ball::update(const sf::Time& dt)
{
    mShape.move(getVelocity() * addMultiplier(getSpeedMultiplier().increasingMultiplier) * dt.asSeconds());
}
    // Reset Ball
const void Ball::resetBall()
{
    float xPosition = getBounds().x / 2 - mShape.getRadius();
    float yPosition = getBounds().y / 2 - mShape.getRadius();
    mShape.setPosition(xPosition, yPosition);

    resetDirection();
    resetMultiplier();
}
