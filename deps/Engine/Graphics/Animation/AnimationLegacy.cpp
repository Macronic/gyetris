#include "AnimationLegacy.hpp"

AnimationLegacy::AnimationLegacy(Window* window) : Animation(window) { }

void AnimationLegacy::load()
{
    texture.create(window->getW() * EngineGlobals::Graphics::fontSize, window->getH() * EngineGlobals::Graphics::fontSize);
}

void AnimationLegacy::update()
{
    texture.clear();
}

void AnimationLegacy::draw()
{
    texture.display();
    auto sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite);
    sprite->setTexture(texture.getTexture());
    window->draw(sprite);
}

void AnimationLegacy::print(std::string string, size_t x, size_t y, sf::Color color)
{
    SFML::printStringOn(string, x, y, texture, color);
}
