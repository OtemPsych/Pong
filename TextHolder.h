#ifndef TextHolder_H_
#define TextHolder_H_

#include <map>
#include <memory>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace Texts {
    enum ID { Mode, ChangeMode, Player1Controls,
              Player1Score, Player2Contols, Player2Score };
}
class TextHolder :private sf::NonCopyable
{
private:
// Private Data Member
    std::map<Texts::ID, std::unique_ptr<sf::Text>> mTextHolder;

public:
// Public Methods
    const void load(const Texts::ID& id, const sf::Font& font,
                    const std::string& str, const int charSize,
                    const sf::Vector2f& pos, const sf::Color& color);

    sf::Text& get(const Texts::ID& id) const;
};
#endif // TextHolder_H_
