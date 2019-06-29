#include <Game/Entities/Block.hpp>

Block::Block(ColorPair color, char first, char second):
    color(color)
{
    if (first == ' ') first = 'X';
    if (second == ' ') second = 'X';

    this->appearance[0] = first;
    this->appearance[1] = second;
}
#include <iostream>
void Block::draw(Window* win, int x, int y)
{
    if (!win)
        return;
    auto rectangle = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape);
    rectangle->setSize(sf::Vector2f(EngineGlobals::Graphics::fontSize, EngineGlobals::Graphics::fontSize));
    rectangle->setOutlineColor(sf::Color(color.background.red, color.background.green, color.background.blue));
    rectangle->setFillColor(sf::Color(color.background.red, color.background.green, color.background.blue));
    rectangle->setPosition((x + 0.5) * EngineGlobals::Graphics::fontSize, (y + 0.5) * EngineGlobals::Graphics::fontSize);
    win->draw(rectangle);
}

