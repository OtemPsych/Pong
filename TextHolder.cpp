#include "TextHolder.h"

#include <cassert>

// Public Methods
    // Load
const void TextHolder::load(const Texts::ID& id, const sf::Font& font,
                            const std::string& str, const unsigned charSize,
                            const sf::Vector2f& pos, const sf::Color& color)
{
    std::unique_ptr<sf::Text> text(new sf::Text());

    text->setFont(font);
    text->setString(str);
    text->setCharacterSize(charSize);
    text->setOrigin(text->getLocalBounds().width / 2,
                    text->getLocalBounds().height / 2);
    text->setPosition(pos);
    text->setColor(color);

    auto inserted = mTextHolder.insert(std::make_pair(id, std::move(text)));
    assert(inserted.second);
}
    // Get
sf::Text& TextHolder::get(const Texts::ID& id) const
{
    auto found = mTextHolder.find(id);
    assert(found != mTextHolder.end());

    return *found->second;
}
    // Fade Text
const void TextHolder::fadeText(const Texts::ID& id, const float rate) const
{
    auto& text = get(id);
    if (text.getColor().a > 0.f)
        text.setColor(sf::Color(text.getColor().r,
                                text.getColor().g,
                                text.getColor().b,
                                (text.getColor().a - rate >= 0.f) ? text.getColor().a - rate
                                                                  : 0.f));
}
