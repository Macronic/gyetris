#include <SFML/Graphics.hpp>
#include <Engine/EngineGlobals.hpp>
#include <GUI/EventHandler.h>
#ifndef ARCADETEXTBOX_H
#define ARCADETEXTBOX_H

class ArcadeTextBox : public sf::Drawable, public sf::Transformable, EventHandler
{
    std::string content;
    std::string availableCharacters;
    size_t maximalTextLength;

    sf::Font* font;
    unsigned int characterSize;

    size_t blinkTime;
    bool willBlinkNow;
    sf::Clock blinkClock;

    void invalidate();
    void calculateSize();
    sf::Vector2i lastSize;
  public:
    ArcadeTextBox();

    bool handleEvent(sf::Event event);
    sf::Vector2i getSize();
    void setAvailableCharacters(std::string characters);
    void setMaximalTextLength(size_t maximalTextLength);
    void setCharacterSize(unsigned int characterSize);
    void setFont(sf::Font& font);
    void setBlinkTime(size_t time);
    void update();
    std::string getText() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // ARCADETEXTBOX_H
