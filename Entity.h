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
    Type         mType;
    sf::Vector2f mVelocity;
    sf::Vector2f mWindowBounds;

public:
// Constructors
    Entity(const Type& type, const sf::Vector2f& bounds);
// Public Methods
    virtual const void update(const sf::Time& dt) = 0;

    inline const void setVelocity(const sf::Vector2f& velocity) { mVelocity = velocity; }
    inline const sf::Vector2f& getVelocity() const { return mVelocity; }
    inline const sf::Vector2f& getBounds() const { return mWindowBounds; }

};
#endif // Entity_H_
