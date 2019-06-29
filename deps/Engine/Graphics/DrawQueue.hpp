#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#ifndef DRAWQUEUE_H
#define DRAWQUEUE_H

class DrawQueue : public sf::Drawable
{
    typedef std::shared_ptr<sf::Drawable> SharedDrawable;

    std::vector<SharedDrawable> queue;
    sf::Vector2i position;

public:
    DrawQueue();
    void apply(sf::RenderTarget& target, sf::Transform transformMatrix = sf::Transform()) const;
    void add(SharedDrawable drawable);
    void clear();

    void setPosition(sf::Vector2i position);
    sf::Vector2i getPosition() const;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Transform getTransformMatrix() const;


};

#endif // DRAWQUEUE_H
