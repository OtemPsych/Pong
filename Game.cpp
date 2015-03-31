#include "Game.h"

#include <SFML/Window/Event.hpp>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

// Constructor
Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Pong", sf::Style::Close
                                             | sf::Style::Titlebar)
    , mTextHolder()
    , mWorld(mTextHolder, mWindow)
    , mGameMode()
{
    mWindow.setFramerateLimit(720);

    mGameMode.AIvAI = true;
    mGameMode.PvAI = mGameMode.PvP = false;

    loadTexts();
    setModeText();
}

// Private Methods
    // Process Events
const void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::KeyPressed:
            handleInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handleInput(event.key.code, false);
        }
    }
}
    // Update
const void Game::update(const sf::Time& dt)
{
    mWorld.update(dt);

    mTextHolder.fadeText(mTextHolder.get(Texts::Mode), 3.f);
    mTextHolder.fadeText(mTextHolder.get(Texts::Player1Controls), 2.5f);
    mTextHolder.fadeText(mTextHolder.get(Texts::Player2Controls), 2.5f);
}
    // Handle Input
const void Game::handleInput(const sf::Keyboard::Key& key,
                             const bool isPressed)
{
    mWorld.handleInput(key, isPressed);

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
            setModeText();
            mWorld.resetGame();
        }
}
    // Handle AI
const void Game::handleAI(const sf::Time& dt)
{
    const bool mode = mGameMode.AIvAI;

    if (mGameMode.PvAI || mGameMode.AIvAI)
        mWorld.handleAI(mode, dt);
}
    // Render
const void Game::render()
{
    mWindow.clear();
    mWorld.draw();
    mWindow.display();
}
    // Set Mode Text
const void Game::setModeText() const
{
    auto& player1 = mTextHolder.get(Texts::Player1Controls);
    auto& player2 = mTextHolder.get(Texts::Player2Controls);

    if (mGameMode.PvAI) {
        mTextHolder.correctProperties(player1);
        mTextHolder.fadeText(player2, 255.f);
    }
    else if (mGameMode.PvP) {
        mTextHolder.correctProperties(player1);
        mTextHolder.correctProperties(player2);
    }
    else if (mGameMode.AIvAI) {
        mTextHolder.fadeText(player1, 255.f);
        mTextHolder.fadeText(player2, 255.f);
    }

    auto& mode = mTextHolder.get(Texts::Mode);
    mode.setString(getGameModeString());
    mTextHolder.correctProperties(mode);
}
    // Get Game Mode String
const std::string Game::getGameModeString() const
{
    if (mGameMode.PvAI)
        return "Player vs AI";
    else if (mGameMode.PvP)
        return "Player vs Player";
    else
        return "AI vs AI";
}
    // Load Texts
const void Game::loadTexts()
{
    mTextHolder.load(Texts::Mode, getGameModeString(), 35.f,
                     sf::Vector2f(mWindow.getSize().x / 2, 95.f), sf::Color::White);

    mTextHolder.load(Texts::ChangeMode, "Press 'T' to change Game Mode", 15.f,
                     sf::Vector2f(mWindow.getSize().x - 150.f, mWindow.getSize().y - 20.f),
                     sf::Color::White);

    mTextHolder.load(Texts::Player1Controls, "Player 1\nW | S", 15.f,
                     sf::Vector2f(mWindow.getSize().x / 2 - mWindow.getSize().x / 3, 70.f),
                     sf::Color::White);

    mTextHolder.load(Texts::Player2Controls, "Player 2\nUp | Down", 15.f,
                     sf::Vector2f(mWindow.getSize().x / 2 + mWindow.getSize().x / 3, 70.f),
                     sf::Color::White);

    mWorld.setFonts();
}

// Public Methods
    // Run
const void Game::run()
{
    sf::Clock clock;
    sf::Time TimeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        TimeSinceLastUpdate += clock.restart();
        while (TimeSinceLastUpdate > TimePerFrame)
        {
            TimeSinceLastUpdate -= TimePerFrame;
            processEvents();
            mWorld.handleCollision();
            update(TimePerFrame);
            handleAI(TimePerFrame);
        }
        render();
    }
}
