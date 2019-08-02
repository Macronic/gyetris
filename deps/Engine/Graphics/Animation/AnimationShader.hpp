#ifndef ANIMATIONSHADER_HPP
#define ANIMATIONSHADER_HPP

#include <SFML/Graphics.hpp>
#include <Engine/Graphics/Animation.hpp>

/// An almost empty class to use with a shader
class RectangleForShader : public sf::Drawable
{
    sf::RectangleShape shape;
    sf::Shader* shader;

  public:
    RectangleForShader(sf::Shader& shader);

    void setShape(int width, int height);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

/// AnimationShader class
/// It can be used to play some shaders on the background
/// The shader should be using parameters:
///   int currentLineHeight
///   float time
///   float timeFromLastClear
///   int sizeOfLastClear
class AnimationShader : public Animation
{
    sf::Shader shader;
    std::shared_ptr<RectangleForShader> rect;

    sf::Clock clock;
    size_t currentLineHeight;
    bool played;

  public:
    AnimationShader(Window* window, std::string vertexFilename, std::string fragmentFilename);

    virtual ~AnimationShader() override;

    void load() override;
    void update() override;
    void draw() override;

    void handleEvent(GameEvent type) override;
};

#endif // ANIMATIONSHADER_HPP
