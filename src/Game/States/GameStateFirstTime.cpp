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
    layout(NULL),
    name("")
{ }
GameStateFirstTime::~GameStateFirstTime()
{ }
void GameStateFirstTime::load()
{
    this->layout = new LayoutFirstTime(80, 24);
}

void GameStateFirstTime::unload()
{
    SAFE_DELETE(this->layout);
}

void GameStateFirstTime::update()
{
    // User typed already
    if (! this->name.empty())
    {
        Globals::Profiles::current = new Profile(this->name);
        StateManager::change(new GameStateMainMenu());
    }
}
#include <iostream>
void GameStateFirstTime::draw()
{
    // BIG HACK
    //
    // As in yetris, there's for now a hack. Making new profile is in terminal!

    std::cout <<
              "Hello, there!\n"
              "It seems this is your first time running yetris.\n"
              "\n"
              "Please enter a profile name.\n"
              "It'll store all your settings, scores and game statistics.\n";

    std::cout << "Provide your name: " << std::endl;;
    std::string name;
    std::cin >> name;

    if (Profile::isNameValid(name))
    {
        this->name = name;
    }
}

