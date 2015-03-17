#include "World.h"

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

    mGameMode.PvAI = true;
    mGameMode.PvP = false;
    mGameMode.AIvAI = false;

    mFont.loadFromFile("Media/Sansation.ttf");

    setFont();

    mChangeModeText.setFont(mFont);
    mChangeModeText.setString("Press 'T' to change Game Mode");
    mChangeModeText.setCharacterSize(15);
    mChangeModeText.setOrigin(mChangeModeText.getLocalBounds().width / 2,
                              mChangeModeText.getLocalBounds().height / 2);
    mChangeModeText.setPosition(mWindow.getSize().x - 150.f, mWindow.getSize().y - 20.f);
    mChangeModeText.setColor(sf::Color::White);

    mPaddle1.setFont(mFont);
    mPaddle2.setFont(mFont);
}

// Private Method
    // Set Font
const void World::setFont()
{
    mModeText.setFont(mFont);
    setModeText();
    mModeText.setCharacterSize(45);
    mModeText.setOrigin(mModeText.getLocalBounds().width / 2,
                        mModeText.getLocalBounds().height / 2);
    mModeText.setPosition(mWindow.getSize().x / 2, 95.f);
    mModeText.setColor(sf::Color::White);
}

// Public Methods
    // Update
const void World::update(const sf::Time& dt)
{
    if (mGameMode.PvAI || mGameMode.AIvAI)
        handleAI();
    handleCollision();

    if (mBall.getSpeedMultiplier().multiplier == mBall.getSpeedMultiplier().originalMultiplier) {
        mPaddle1.resetMultiplier();
        mPaddle2.resetMultiplier();
    }

    mPaddle1.update(dt);
    mPaddle2.update(dt);
    mBall.update(dt);

    if (mModeText.getColor().a > 0) {
        int a = mModeText.getColor().a;
        mModeText.setColor(sf::Color(255,255,255,a -= 3.f));
    }
}
    // Handle Input
const void World::handleInput(const sf::Keyboard::Key& key, const bool isPressed)
{
    if (mGameMode.PvAI || mGameMode.PvP) {
        if (key == sf::Keyboard::W)
            mPaddle1.getMovement().UP = isPressed;
        if (key == sf::Keyboard::S)
            mPaddle1.getMovement().DOWN = isPressed;
    }

    if (mGameMode.PvP) {
        if (key == sf::Keyboard::Up)
            mPaddle2.getMovement().UP = isPressed;
        if (key == sf::Keyboard::Down)
            mPaddle2.getMovement().DOWN = isPressed;
    }

    if (isPressed)
        if (key == sf::Keyboard::T) {
            if (mGameMode.PvAI) {
                mGameMode.PvP = true;
                mGameMode.PvAI = false;
            }
            else if (mGameMode.PvP) {
                mGameMode.AIvAI = true;
                mGameMode.PvP = false;
            }
            else if (mGameMode.AIvAI) {
                mGameMode.PvAI = true;
                mGameMode.AIvAI = false;
            }
            resetGame();
            setModeText();
        }
}
    // Handle AI
const void World::handleAI()
{
    if (mGameMode.AIvAI)
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

    if (mModeText.getColor().a > 0)
        mWindow.draw(mModeText);

    mWindow.draw(mChangeModeText);
}
    // Reset Game
const void World::resetGame()
{
    Paddle newPaddle1(Paddle::LEFT, Entity::PADDLE, sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));
    Paddle newPaddle2(Paddle::RIGHT, Entity::PADDLE, sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));
    Ball newBall(Entity::BALL, sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));

    mPaddle1 = newPaddle1;
    mPaddle2 = newPaddle2;
    mBall = newBall;

    mPaddle1.setFont(mFont);
    mPaddle2.setFont(mFont);
}
    // Set Mode Text
const void World::setModeText()
{
    if (mGameMode.PvAI)
        mModeText.setString("Player vs AI");
    else if (mGameMode.PvP)
        mModeText.setString("Player vs Player");
    else if (mGameMode.AIvAI)
        mModeText.setString("AI vs AI");

    mModeText.setOrigin(mModeText.getLocalBounds().width / 2,
                        mModeText.getLocalBounds().height / 2);
    mModeText.setPosition(mWindow.getSize().x / 2, 95.f);
    mModeText.setColor(sf::Color(255, 255, 255, 255));
}
