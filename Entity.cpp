#include "Entity.h"

// Constructor
Entity::Entity(const Type& type, const sf::Vector2f& bounds)
    : mType(type)
    , mWindowBounds(bounds)
{
    mVelocity =
        (mType == PADDLE) ? sf::Vector2f(0.f, 500.f)
                          : sf::Vector2f(400.f, 250.f);

    mSpeedMultiplier.increasingMultiplier =
        (mType == PADDLE) ? 0.0002f
                          : 0.0005f;

    mSpeedMultiplier.originalSpeed = mVelocity;
    mSpeedMultiplier.originalMultiplier = mSpeedMultiplier.multiplier = 1.f;
}
