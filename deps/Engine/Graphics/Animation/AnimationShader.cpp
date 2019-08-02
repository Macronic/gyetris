#include "AnimationShader.hpp"

AnimationShader::AnimationShader(Window* window, std::string vertexFilename, std::string fragmentFilename):
    Animation(window),
    rect(new RectangleForShader(shader))
{
    shader.loadFromFile(vertexFilename, fragmentFilename);
    shader.setParameter("texture", sf::Shader::CurrentTexture);

}

AnimationShader::~AnimationShader() { }

void AnimationShader::load()
{
    clock.restart();
    rect->setShape(window->getW() * EngineGlobals::Graphics::fontSize, window->getH() * EngineGlobals::Graphics::fontSize);

    GameEventsManager::registerListener(this, GameEventType::CLEAR_LINES_EVENT);
    GameEventsManager::registerListener(this, GameEventType::HEIGHT_CHANGED_EVENT);
    GameEventsManager::registerListener(this, GameEventType::START_GAME_EVENT);
    GameEventsManager::registerListener(this, GameEventType::STOP_GAME_EVENT);

}

void AnimationShader::update()
{
    shader.setUniform("time", clock.getElapsedTime().asSeconds());
    shader.setUniform("played", played);
    shader.setUniform("currentLineHeight", (int)currentLineHeight);
}

void AnimationShader::draw()
{
    window->draw(rect);
}

void AnimationShader::handleEvent(GameEvent event)
{
    switch(event.index())
    {
        case GameEventType::CLEAR_LINES_EVENT:
            break;
        case GameEventType::HEIGHT_CHANGED_EVENT:
            currentLineHeight = std::get<GameEventType::HEIGHT_CHANGED_EVENT>(event);
            break;
        case GameEventType::START_GAME_EVENT:
            played = true;
            break;
        case GameEventType::STOP_GAME_EVENT:
            played = false;
            break;
        default:
            break;
    }
}


RectangleForShader::RectangleForShader(sf::Shader& shader):
    shader(&shader) { }

void RectangleForShader::setShape(int width, int height)
{
    shape = sf::RectangleShape(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(15);
}

void RectangleForShader::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, shader);
}
