#include "DrawQueue.hpp"

DrawQueue::DrawQueue() { }

void DrawQueue::apply(sf::RenderTarget& target, sf::Transform transformMatrix) const
{
    transformMatrix.combine(getTransformMatrix());
    for (SharedDrawable drawable : queue)
    {
        target.draw(*drawable, sf::RenderStates(transformMatrix));
    }
}

void DrawQueue::add(SharedDrawable drawable)
{
    queue.push_back(drawable);
}

void DrawQueue::clear()
{
    queue.clear();
}

void DrawQueue::setPosition(sf::Vector2i position)
{
    this->position = position;
}

sf::Vector2i DrawQueue::getPosition() const
{
    return position;
}

void DrawQueue::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    apply(target, states.transform);
}

sf::Transform DrawQueue::getTransformMatrix() const
{
    sf::Transform ret;
    ret.translate(position.x, position.y);
    return ret;
}
