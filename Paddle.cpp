#include "Paddle.h"

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

template <typename T>
std::string NumberToString(T num)
{
    std::ostringstream temp;
    temp << num;
    return temp.str();
}

// Constructor
Paddle::Paddle(const Side& side, const Type& type,
               const sf::Vector2f& bounds)
    : Entity(type, bounds)
    , mSide(side)
    , mScore(0)
{
// Set Bounds
    sf::FloatRect shapeBounds = mShape.getLocalBounds();
    mShape.setOrigin(shapeBounds.width / 2, shapeBounds.height / 2);
// Set Size
    mShape.setSize(sf::Vector2f(12.f, 120.f));
// Set Position
    float leftPosition = 10.f;
    float rightPosition = bounds.x - mShape.getSize().x - 10.f;
    float yPosition = bounds.y / 2 - mShape.getSize().y / 2;
    mShape.setPosition((side == LEFT ? leftPosition : rightPosition), yPosition);
// Set Color
    mShape.setFillColor(sf::Color::White);
// Falsify Movement
    mMovement.UP = mMovement.DOWN = false;
}

// Public Methods
    // Handle AI
const void Paddle::handleAI(Ball& ball)
{
// Predict Trajectory
    if (ball.getVelocity().x < 0.f)             // Ball going Left
    {
        if (ball.getVelocity().y < 0.f)         // Ball going Up
        {
            double newXPosition = ball.getShape().getPosition().x;
            double newYPosition = ball.getShape().getPosition().y;
            while ((newXPosition - (-ball.getVelocity().x)) > 0.f) {
                newXPosition -= -ball.getVelocity().x;
                newYPosition -= -ball.getVelocity().y;
            }
            if (newYPosition < 0.f)
                std::cout << "WALL: Left | Up\n";
        }
        else if (ball.getVelocity().y > 0.f)    // Ball going Down
        {
            double newXPosition = ball.getShape().getPosition().x;
            double newYPosition = ball.getShape().getPosition().y;
            while ((newXPosition - (-ball.getVelocity().x)) > 0.f) {
                newXPosition -= -ball.getVelocity().x;
                newYPosition += ball.getVelocity().y;
            }
            if (newYPosition > getBounds().y)
                std::cout << "WALL: Left | Down\n";
        }
    }
    else if (ball.getVelocity().x > 0.f)        // Ball going Right
    {
        if (ball.getVelocity().y < 0.f)         // Ball going Up
        {
            double newXPosition = ball.getShape().getPosition().x;
            double newYPosition = ball.getShape().getPosition().y;
            while ((newXPosition + ball.getVelocity().x < getBounds().x)) {
                newXPosition += ball.getVelocity().x;
                newYPosition -= -ball.getVelocity().y;
            }
            if (newYPosition < 0.f)
                std::cout << "WALL: Right | Up\n";
        }
        else if (ball.getVelocity().y > 0.f)    // Ball going Down
        {
            double newXPosition = ball.getShape().getPosition().x;
            double newYPosition = ball.getShape().getPosition().y;
            while ((newXPosition + ball.getVelocity().x < getBounds().x)) {
                newXPosition += ball.getVelocity().x;
                newYPosition += ball.getVelocity().y;
            }
            if (newYPosition > getBounds().y)
                std::cout << "WALL: Right | DOWN\n";
        }
    }
// Recenter paddle if ball is not heading towards it
    if ((mSide == RIGHT && ball.getVelocity().x < 0.f) || (mSide == LEFT && ball.getVelocity().x > 0.f)){
        if (mShape.getPosition().y + mShape.getSize().y / 2 < getBounds().y / 2)
            mMovement.DOWN = true;
        else if (mShape.getPosition().y + mShape.getSize().y / 2 > getBounds().y / 2)
            mMovement.UP = true;
    }
    else {
// Chase Ball
        if (mShape.getPosition().y > ball.getShape().getPosition().y + ball.getShape().getRadius() * 2) {
            mMovement.UP = true;
            mMovement.DOWN = false;
        }
        else if (mShape.getPosition().y + mShape.getSize().y < ball.getShape().getPosition().y) {
            mMovement.DOWN = true;
            mMovement.UP = false;
        }
    }
}
    // Check Collision
const void Paddle::checkCollision()
{
    if (mShape.getPosition().y < 0.f)
        mMovement.UP = false;
    else if (mShape.getPosition().y + mShape.getSize().y > getBounds().y)
        mMovement.DOWN = false;
}
    // Update
const void Paddle::update(const sf::Time& dt)
{
    mScoreText.setString(NumberToString(mScore));

    float yMovement = 0.f;
    if (mMovement.UP)
        yMovement -= getVelocity().y;
    if (mMovement.DOWN)
        yMovement += getVelocity().y;

    mShape.move(sf::Vector2f(0.f, yMovement) * dt.asSeconds());
}
    // Set Font
const void Paddle::setFont(const sf::Font& font)
{
    mScoreText.setFont(font);
    mScoreText.setString(NumberToString(mScore));
    mScoreText.setCharacterSize(48);
    mScoreText.setOrigin(mScoreText.getLocalBounds().width / 2,
                         mScoreText.getLocalBounds().height / 2);
    if (mSide == LEFT)
        mScoreText.setPosition(getBounds().x / 2 - 65.f, 15.f);
    else
        mScoreText.setPosition(getBounds().x / 2 + 65.f, 15.f);
    mScoreText.setColor(sf::Color::White);
}
