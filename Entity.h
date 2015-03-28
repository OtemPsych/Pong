#ifndef Entity_H_
#define Entity_H_

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Entity
{
public:
    enum Type { PADDLE, BALL };
private:
// Private Data Members
    Type            mType;
    sf::Vector2f    mVelocity;

    struct Speed {
    sf::Vector2f originalSpeed;
    float        originalMultiplier,
                 multiplier,
                 increasingMultiplier;
    }               mSpeedMultiplier;

    sf::Vector2f    mWindowBounds;

public:
// Constructors
    Entity(const Type& type, const sf::Vector2f& bounds);
// Public Methods
    virtual const void update(const sf::Time& dt) = 0;
    // Speed Multipliers
    inline const float addMultiplier(const float multiplier) { return mSpeedMultiplier.multiplier += multiplier; }
    inline const Speed& getSpeedMultiplier() const { return mSpeedMultiplier; }
    inline const void resetMultiplier() { mSpeedMultiplier.multiplier = mSpeedMultiplier.originalMultiplier; }
    // Velocity
    inline const void setVelocity(const sf::Vector2f& velocity) { mVelocity = velocity; }
    inline const sf::Vector2f& getVelocity() const { return mVelocity; }
    // Bounds
    inline const sf::Vector2f& getBounds() const { return mWindowBounds; }
};
#endif // Entity_H_
