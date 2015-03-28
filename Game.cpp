#include "Game.h"

#include <SFML/Window/Event.hpp>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

// Constructor
Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Pong", sf::Style::Close
                                             | sf::Style::Titlebar)
    , mTextHolder()
    , mWorld(mTextHolder, mWindow)
{
    mWindow.setFramerateLimit(720);

    mGameMode.PvAI = true;
    mGameMode.PvP = false;
    mGameMode.AIvAI = false;

    mFont.loadFromFile("Media/Sansation.ttf");

    loadTexts();
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
            break;
        }
    }
}
    // Update
const void Game::update(const sf::Time& dt)
{
    mWorld.update(dt);

    auto modeText = mTextHolder.get(Texts::Mode);
    if (modeText.getColor().a > 0) {
        int a = modeText.getColor().a;
        modeText.setColor(sf::Color(255,255,255,a -= 3.f));
    }
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
            mWorld.resetGame(mFont);
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
const void Game::setModeText()
{
    auto& mode = mTextHolder.get(Texts::Mode);

    if (mGameMode.PvAI)
        mode.setString("Player vs AI");
    else if (mGameMode.PvP)
        mode.setString("Player vs Player");
    else if (mGameMode.AIvAI)
        mode.setString("AI vs AI");

    mode.setOrigin(mode.getLocalBounds().width / 2,
                   mode.getLocalBounds().height / 2);
    mode.setPosition(mWindow.getSize().x / 2, 95.f);
    mode.setColor(sf::Color::White);
}
    // Load Texts
const void Game::loadTexts()
{
    mTextHolder.load(Texts::Mode, mFont, "Player vs AI", 45.f,
                     sf::Vector2f(mWindow.getSize().x / 2, 95.f), sf::Color::White);

    mTextHolder.load(Texts::ChangeMode, mFont, "Press 'T' to change Game Mode", 15.f,
                     sf::Vector2f(mWindow.getSize().x - 150.f, mWindow.getSize().y - 20.f),
                     sf::Color::White);

    mWorld.setFonts(mFont);
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
