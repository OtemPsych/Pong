#include "Entity.h"

// Constructor
Entity::Entity(const Type& type, const sf::Vector2f& bounds)
    : mType(type)
    , mWindowBounds(bounds)
{
    (mType == PADDLE) ? (mVelocity = sf::Vector2f(0.f, 500.f))
                      : (mVelocity = sf::Vector2f(400.f, 250.f));

    mSpeedMultiplier.originalSpeed = mVelocity;
    mSpeedMultiplier.originalMultiplier = mSpeedMultiplier.multiplier = 1.f;
    mSpeedMultiplier.increasingMultiplier = 0.0005f;
}
