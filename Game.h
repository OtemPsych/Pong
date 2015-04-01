#ifndef Game_H_
#define Game_H_

#include "World.h"

class Game :private sf::NonCopyable
{
private:
// Private Data Members
    sf::RenderWindow mWindow;
    TextHolder       mTextHolder;

    World            mWorld;
    sf::Time         mMatchLength;
    struct {
        bool PvP,
             PvAI,
             AIvAI;
    }                mGameMode;

// Private Methods
    const void processEvents();
    const void update(const sf::Time& dt);
    const void handleInput(const sf::Keyboard::Key& key,
                           const bool isPressed);
    const void handleAI(const sf::Time& dt);
    const void render();

    const void setModeText() const;
    const std::string getGameModeString() const;
    const std::string getMatchLengthString() const;
    const void resetMatchLength() const;
    const void loadTexts();

public:
// Constructor
    Game();
// Public Method
    const void run();
};
#endif // Game_H_
