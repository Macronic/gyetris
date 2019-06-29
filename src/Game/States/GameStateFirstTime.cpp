#include <Game/States/GameStateFirstTime.hpp>
#include <Game/States/GameStateMainMenu.hpp>
#include <Game/Entities/Profile.hpp>
#include <Engine/Flow/StateManager.hpp>
#include <Engine/Helpers/Utils.hpp>
#include <Engine/Helpers/File.hpp>
#include <Engine/Graphics/SFML.hpp>
#include <Game/Config/Globals.hpp>

#include <cstring>

GameStateFirstTime::GameStateFirstTime():
    layout(nullptr),
    name("")
{ }
GameStateFirstTime::~GameStateFirstTime()
{ }
void GameStateFirstTime::load()
{
    this->layout = new LayoutFirstTime(SFML::getWidth(), SFML::getHeight());
}

void GameStateFirstTime::unload()
{
    SAFE_DELETE(this->layout);
}

void GameStateFirstTime::update()
{
    if (!this->name.empty())
    {
        Globals::Profiles::current = new Profile(this->name);
        StateManager::change(new GameStateMainMenu());
    }
}

bool GameStateFirstTime::handleEvent(sf::Event event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Return)
            {
                name = this->layout->getUserName();
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

void GameStateFirstTime::draw()
{
    this->layout->draw();
}

