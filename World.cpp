#include "World.h"

#include <string>
#include <sstream>

// Constructor
World::World(sf::RenderWindow& window)
    : mPaddle1(Paddle::LEFT, Entity::PADDLE, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mPaddle2(Paddle::RIGHT, Entity::PADDLE, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mBall(Entity::BALL, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mWindow(window)
{
    line.setSize(sf::Vector2f(2.f, mWindow.getSize().y));
    line.setPosition(mWindow.getSize().x / 2, 0.f);
    line.setFillColor(sf::Color::White);

    mFont.loadFromFile("Media/Sansation.ttf");

    mPaddle1.setFont(mFont);
    mPaddle2.setFont(mFont);
}

// Public Methods
    // Update
const void World::update(const sf::Time& dt)
{
    handleAI();
    handleCollision();

    mPaddle1.update(dt);
    mPaddle2.update(dt);
    mBall.update(dt);
}
    // Handle Input
const void World::handleInput(const sf::Keyboard::Key& key, const bool isPressed)
{

}
    // Handle AI
const void World::handleAI()
{
    mPaddle1.handleAI(mBall);
    mPaddle2.handleAI(mBall);
}
    // Handle Collision
const void World::handleCollision()
{
    mPaddle1.checkCollision();
    mPaddle2.checkCollision();
    mBall.checkCollision(mPaddle1, mPaddle2);
}
    // Draw
const void World::draw()
{
    mWindow.draw(mPaddle1.getShape());
    mWindow.draw(mPaddle2.getShape());
    mWindow.draw(mBall.getShape());

    mWindow.draw(line);

    mWindow.draw(mPaddle1.getScoreText());
    mWindow.draw(mPaddle2.getScoreText());
}
