#include "ArcadeTextBox.h"

void ArcadeTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Text text;
    text.setFont(*font);
    text.setPosition(getPosition());
    text.setOrigin(getOrigin());
    text.setScale(getScale());
    text.setRotation(getRotation());
    text.setCharacterSize(characterSize);

    if (content.length() < maximalTextLength && willBlinkNow)
        text.setString(content + "_");
    else
        text.setString(content);

    target.draw(text);
}

void ArcadeTextBox::invalidate()
{
    lastSize = sf::Vector2i(-1, -1);
}

void ArcadeTextBox::calculateSize()
{
    sf::Text text;
    text.setFont(*font);
    if (content.length() < maximalTextLength)
        text.setString(content + "_");
    else
        text.setString(content);
    text.setCharacterSize(characterSize);
    text.setOrigin(getOrigin());
    text.setScale(getScale());
    text.setRotation(getRotation());

    sf::Rect<float> rect = text.getLocalBounds();
    lastSize = sf::Vector2i(rect.width, rect.height);
}

ArcadeTextBox::ArcadeTextBox() :
    availableCharacters("abcdefghijklmnoprstuwxyzABCDEFGHIJKLMNOPRSTUWXYZ0123456789"),
    maximalTextLength(16),
    font(EngineGlobals::Graphics::font),
    characterSize(static_cast<unsigned int>(EngineGlobals::Graphics::fontSize)),
    blinkTime(400),
    willBlinkNow(false) { }

bool ArcadeTextBox::handleEvent(sf::Event event)
{
    switch (event.type)
    {
        case sf::Event::TextEntered:
            if (maximalTextLength > content.length() && availableCharacters.find(static_cast<char>(event.text.unicode)) != std::string::npos)
            {
                content += static_cast<char>(event.text.unicode);
                invalidate();
                return true;
            }
            break;

        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
                case sf::Keyboard::Backspace:
                    if (content.length() > 0)
                    {
                        content.erase(content.end() - 1);
                        invalidate();
                        return true;
                    }
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
    return false;
}

sf::Vector2i ArcadeTextBox::getSize()
{
    if (lastSize == sf::Vector2i(-1, -1))
    {
        calculateSize();
    }
    return lastSize;
}

void ArcadeTextBox::setAvailableCharacters(std::string characters)
{
    this->availableCharacters = characters;
}

void ArcadeTextBox::setMaximalTextLength(size_t maximalTextLength)
{
    this->maximalTextLength = maximalTextLength;
}

void ArcadeTextBox::setCharacterSize(unsigned int characterSize)
{
    this->characterSize = characterSize;
}

void ArcadeTextBox::setFont(sf::Font& font)
{
    this->font = &font;
}

void ArcadeTextBox::setBlinkTime(size_t time)
{
    this->blinkTime = time;
}

void ArcadeTextBox::update()
{
    if (blinkClock.getElapsedTime().asMilliseconds() >= blinkTime)
    {
        blinkClock.restart();
        willBlinkNow = !willBlinkNow;
    }
}

std::string ArcadeTextBox::getText() const
{
    return content;
}

