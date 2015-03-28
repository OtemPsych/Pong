#include "Game.h"

#include <SFML/Window/Event.hpp>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

// Constructor
Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Pong", sf::Style::Close
                                             | sf::Style::Titlebar)
    , mWorld(mWindow)
{
    mWindow.setFramerateLimit(720);
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
}
    // Handle Input
const void Game::handleInput(const sf::Keyboard::Key& key, const bool isPressed)
{
    mWorld.handleInput(key, isPressed);
}
    // Render
const void Game::render()
{
    mWindow.clear();
    mWorld.draw();
    mWindow.display();
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
            update(TimePerFrame);
        }
        render();
    }
}
