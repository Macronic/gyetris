#ifndef ANIMATIONLEGACY_H
#define ANIMATIONLEGACY_H

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <Engine/Graphics/Animation.hpp>
#include <Engine/Graphics/SFML.hpp>

/// Animation class, made for easy porting of AnimationFire and others from ncurses to SFML.
class AnimationLegacy : public Animation
{

  protected:
    sf::RenderTexture texture;

  public:
    AnimationLegacy(Window* window);

    virtual void load() override;
    virtual void update() override;
    virtual void draw() override;

    void print(std::string string, size_t x, size_t y, sf::Color color = sf::Color::White);
};

#endif // ANIMATIONLEGACY_H
