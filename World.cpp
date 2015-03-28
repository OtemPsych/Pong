#include "World.h"

// Constructor
World::World(TextHolder& holder, sf::RenderWindow& window)
    : mPaddle1(Paddle::LEFT, Entity::PADDLE, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mPaddle2(Paddle::RIGHT, Entity::PADDLE, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mBall(Entity::BALL, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mBallPrediction(Entity::BALL, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mBallMultiplier(4.f)
    , mTextHolder(holder)
    , mWindow(window)
{
    line.setSize(sf::Vector2f(2.f, mWindow.getSize().y));
    line.setPosition(mWindow.getSize().x / 2, 0.f);
    line.setFillColor(sf::Color::White);

    mBallPrediction = mBall;
    mBallPrediction.setVelocity(sf::Vector2f(mBall.getVelocity().x * mBallMultiplier,
                                             mBall.getVelocity().y * mBallMultiplier));
}

// Public Methods
    // Update
const void World::update(const sf::Time& dt)
{
    if (mBall.getSpeedMultiplier().multiplier == mBall.getSpeedMultiplier().originalMultiplier) {
        mPaddle1.resetMultiplier();
        mPaddle2.resetMultiplier();
    }

    mPaddle1.update(dt);
    mPaddle2.update(dt);
    mBall.update(dt);
    mBallPrediction.update(dt);

    if (mBall.getCollisionCheck()) {
        mBallPrediction = mBall;
        mBallPrediction.setVelocity(sf::Vector2f(mBall.getVelocity().x * mBallMultiplier, mBall.getVelocity().y * mBallMultiplier));
    }

    checkScoreChanges();
    mTextHolder.fadeText(Texts::Player1Controls, 1.f);
    mTextHolder.fadeText(Texts::Player2Controls, 1.f);
}
    // Handle Input
const void World::handleInput(const sf::Keyboard::Key& key, const bool isPressed)
{
    if (key == sf::Keyboard::W)
        mPaddle1.getMovement().UP = isPressed;
    if (key == sf::Keyboard::S)
        mPaddle1.getMovement().DOWN = isPressed;

    if (key == sf::Keyboard::Up)
        mPaddle2.getMovement().UP = isPressed;
    if (key == sf::Keyboard::Down)
        mPaddle2.getMovement().DOWN = isPressed;
}
    // Handle AI
const void World::handleAI(const bool mode, const sf::Time& dt)
{
    if (mode)
        mPaddle1.handleAI(mBall, mBallPrediction, mBallMultiplier, dt);
    mPaddle2.handleAI(mBall, mBallPrediction, mBallMultiplier, dt);
}
    // Handle Collision
const void World::handleCollision()
{
    mPaddle1.handleCollision();
    mPaddle2.handleCollision();

    mBall.handleCollision(mPaddle1, mPaddle2, true);
    mBallPrediction.handleCollision(mPaddle1, mPaddle2, false);
}
    // Draw
const void World::draw()
{
    // Entities
    mWindow.draw(mPaddle1.getShape());
    mWindow.draw(mPaddle2.getShape());
    mWindow.draw(mBall.getShape());
    mWindow.draw(line);

    // Scores
    mWindow.draw(mTextHolder.get(Texts::Player1Score));
    mWindow.draw(mTextHolder.get(Texts::Player2Score));

    // Game Mode
    auto& modeText = mTextHolder.get(Texts::Mode);
    if (modeText.getColor().a > 0.f)
        mWindow.draw(modeText);

    // Change Game Mode
    mWindow.draw(mTextHolder.get(Texts::ChangeMode));

    // Player Controls
    auto& player1Controls = mTextHolder.get(Texts::Player1Controls);
    if (player1Controls.getColor().a > 0.f) {
        mWindow.draw(player1Controls);
        mWindow.draw(mTextHolder.get(Texts::Player2Controls));
    }

 //   mWindow.draw(mBallPrediction.getShape());
}
    // Check Score Changes
const void World::checkScoreChanges()
{
    static int paddle1Score = 0;
    static int paddle2Score = 0;

    if (mPaddle1.getScore() != paddle1Score) {
        paddle1Score = mPaddle1.getScore();
        mBallPrediction = mBall;
        mBallPrediction.setVelocity(sf::Vector2f(mBall.getVelocity().x * mBallMultiplier, mBall.getVelocity().y * mBallMultiplier));
        mPaddle1.updateScoreText(mTextHolder.get(Texts::Player1Score));
    }
    else if (mPaddle2.getScore() != paddle2Score) {
        paddle2Score = mPaddle2.getScore();
        mBallPrediction = mBall;
        mBallPrediction.setVelocity(sf::Vector2f(mBall.getVelocity().x * mBallMultiplier, mBall.getVelocity().y * mBallMultiplier));
        mPaddle2.updateScoreText(mTextHolder.get(Texts::Player2Score));
    }
}
    // Reset Game
const void World::resetGame(const sf::Font& font)
{
    Paddle newPaddle1(Paddle::LEFT, Entity::PADDLE, sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));
    Paddle newPaddle2(Paddle::RIGHT, Entity::PADDLE, sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));
    Ball newBall(Entity::BALL, sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));

    mPaddle1 = newPaddle1;
    mPaddle2 = newPaddle2;
    mBall = newBall;
}
    // Set Fonts
const void World::setFonts(const sf::Font& font)
{
    mTextHolder.load(Texts::Player1Controls, font, "Player 1\nW | S to move", 15.f, sf::Vector2f(mWindow.getSize().x / 2 - mWindow.getSize().x / 3, 70.f), sf::Color::White);
    mTextHolder.load(Texts::Player2Controls, font, "Player 2\nUp | Down", 15.f, sf::Vector2f(mWindow.getSize().x / 2 + mWindow.getSize().x / 3, 70.f), sf::Color::White);

    mPaddle1.setFont(mTextHolder, font);
    mPaddle2.setFont(mTextHolder, font);
}
