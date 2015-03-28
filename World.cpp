#include "World.h"

// Constructor
World::World(TextHolder& holder, sf::RenderWindow& window)
    : mPaddle1(Paddle::LEFT, Entity::PADDLE, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mPaddle2(Paddle::RIGHT, Entity::PADDLE, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mBall(Entity::BALL, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mBallPrediction(Entity::BALL, sf::Vector2f(window.getSize().x, window.getSize().y))
    , mBallMultiplier(4)
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

    auto& modeText = mTextHolder.get(Texts::Mode);
    auto& player1Controls = mTextHolder.get(Texts::Player1Controls);
    auto& player2Controls = mTextHolder.get(Texts::Player2Contols);

    checkScoreChanges();

    if (mBall.getCollisionCheck()) {
        mBallPrediction = mBall;
        mBallPrediction.setVelocity(sf::Vector2f(mBall.getVelocity().x * mBallMultiplier, mBall.getVelocity().y * mBallMultiplier));
    }

    if (modeText.getColor().a > 0) {
        int a = modeText.getColor().a;
        modeText.setColor(sf::Color(255,255,255,a -= 3.f));
    }
    if (player1Controls.getColor().a > 0) {
        int a = player1Controls.getColor().a;
        player1Controls.setColor(sf::Color(255,255,255,a -= 1.f));
        player2Controls.setColor(player1Controls.getColor());
    }
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
    mWindow.draw(mPaddle1.getShape());
    mWindow.draw(mPaddle2.getShape());
    mWindow.draw(mBall.getShape());

    mWindow.draw(line);

    auto& modeText = mTextHolder.get(Texts::Mode);
    auto& changeMode = mTextHolder.get(Texts::ChangeMode);
    auto& player1Controls = mTextHolder.get(Texts::Player1Controls);
    auto& player1Score = mTextHolder.get(Texts::Player1Score);
    auto& player2Controls = mTextHolder.get(Texts::Player2Contols);
    auto& player2Score = mTextHolder.get(Texts::Player2Score);

    mWindow.draw(player1Score);
    mWindow.draw(player2Score);

    if (modeText.getColor().a > 0)
        mWindow.draw(modeText);

    mWindow.draw(changeMode);

    if (player1Controls.getColor().a > 0) {
        mWindow.draw(player1Controls);
        mWindow.draw(player2Controls);
    }

 //   mWindow.draw(mBallPrediction.getShape());
}
    // Check Score Changes
const void World::checkScoreChanges()
{
    auto& player1Score = mTextHolder.get(Texts::Player1Score);
    auto& player2Score = mTextHolder.get(Texts::Player2Score);

    static int paddle1Score = 0;
    static int paddle2Score = 0;
    if (mPaddle1.getScore() != paddle1Score) {
        paddle1Score = mPaddle1.getScore();
        mBallPrediction = mBall;
        mBallPrediction.setVelocity(sf::Vector2f(mBall.getVelocity().x * mBallMultiplier, mBall.getVelocity().y * mBallMultiplier));
        mPaddle1.updateScoreText(player1Score);
    }
    else if (mPaddle2.getScore() != paddle2Score) {
        paddle2Score = mPaddle2.getScore();
        mBallPrediction = mBall;
        mBallPrediction.setVelocity(sf::Vector2f(mBall.getVelocity().x * mBallMultiplier, mBall.getVelocity().y * mBallMultiplier));
        mPaddle2.updateScoreText(player2Score);
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
    mTextHolder.load(Texts::Player2Contols, font, "Player 2\nUp | Down", 15.f, sf::Vector2f(mWindow.getSize().x / 2 + mWindow.getSize().x / 3, 70.f), sf::Color::White);

    mPaddle1.setFont(mTextHolder, font);
    mPaddle2.setFont(mTextHolder, font);
}
