#include "Paddle.h"

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
const void Paddle::handleAI(Ball& ball, Ball& futureBall, const int futureBallMultiplier, const sf::Time& dt)
{
// Recenter paddle if ball is not heading towards it
    if ((mSide == RIGHT && ball.getVelocity().x < 0.f) || (mSide == LEFT && ball.getVelocity().x > 0.f)){
        if (mShape.getPosition().y + mShape.getSize().y / 2 < getBounds().y / 2)
            mMovement.DOWN = true;
        else if (mShape.getPosition().y + mShape.getSize().y / 2 > getBounds().y / 2)
            mMovement.UP = true;
    }
    else {
    // Chase Future Ball
        if (mShape.getPosition().y + mShape.getSize().y / 2 > futureBall.getShape().getPosition().y + futureBall.getShape().getRadius() * 2) {
            mMovement.UP = true;
            mMovement.DOWN = false;
        }
        else if (mShape.getPosition().y + mShape.getSize().y / 2 < futureBall.getShape().getPosition().y) {
            mMovement.DOWN = true;
            mMovement.UP = false;
        }
        else {
            mMovement.UP = false;
            mMovement.DOWN = false;
        }
    }
}
    // Check Collision
const void Paddle::handleCollision()
{
    if (mShape.getPosition().y < 0.f)
        mMovement.UP = false;
    else if (mShape.getPosition().y + mShape.getSize().y > getBounds().y)
        mMovement.DOWN = false;
}
    // Update
const void Paddle::update(const sf::Time& dt)
{
    float yMovement = 0.f;
    if (mMovement.UP)
        yMovement -= getVelocity().y;
    if (mMovement.DOWN)
        yMovement += getVelocity().y;

    mShape.move(sf::Vector2f(0.f, yMovement * addMultiplier(getSpeedMultiplier().increasingMultiplier)) * dt.asSeconds());
}
    // Update Score Text
const void Paddle::updateScoreText(sf::Text& text)
{
    text.setString(NumberToString(mScore));
}
    // Set Font
const void Paddle::setFont(TextHolder& holder, const sf::Font& font)
{
    if (mSide == LEFT)
        holder.load(Texts::Player1Score, font, NumberToString(mScore),
                    48, sf::Vector2f(getBounds().x / 2 - 65.f, 15.f), sf::Color::White);
    else
        holder.load(Texts::Player2Score, font, NumberToString(mScore),
                    48, sf::Vector2f(getBounds().x / 2 + 65.f, 15.f), sf::Color::White);
}
