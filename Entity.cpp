#include "Entity.h"

// Constructor
Entity::Entity(const Type& type, const sf::Vector2f& bounds)
    : mType(type)
    , mWindowBounds(bounds)
{
    (mType == PADDLE) ? (mVelocity = sf::Vector2f(0.f, 500.f))
                      : (mVelocity = sf::Vector2f(500.f, 350.f));
}
