#include <Engine/Flow/StateManager.hpp>
#include <Engine/Graphics/SFML.hpp>
#include <Engine/Graphics/Colors.hpp>
#include <Game/Config/Globals.hpp>
#include <Game/Config/Arguments.hpp>
#include <Engine/Helpers/Utils.hpp>
#include <Game/States/GameStateMainMenu.hpp>
#include <Game/States/GameStateFirstTime.hpp>
#include <Engine/InputManager.hpp>
#include <Game/Entities/Profile.hpp>
#include <Engine/Helpers/INI.hpp>

// Welcome to the `yetris` source code!
//
// This is the starting point of the whole game. If you're here to
// understand how this game was made, I strongly suggest you to skim
// through the `README.md` file on this directory.
//
// As soon as you do that you'll be able to figure out what these
// functions below do and (more importantly) what they don't do.
//
// I'm glad you had interest on this. Please visit the `yetris`
// website and consider improving it - even a little bit of help
// counts.

int main(int argc, char* argv[])
{
    try
    {
        // The following initialization order is important

        EngineGlobals::init();
        Globals::init();
        Arguments::parse(argc, argv);

        Utils::Random::init();

        SFML::init();
        Colors::init();

        // Which game screen should we go first?
        // If there's a Profile then we'll go to the game.
        // If not, then we need to ask the user for a Profile name.
        GameState* firstGameState = NULL;

        // Trying to load default profile from config files
        if (!Profile::load())
        {
            // Couldn't find any profiles - first time!
            Globals::Profiles::default_name = "";

            // Let's ask the user for his info
            firstGameState = new GameStateFirstTime();
        }
        else
        {
            // Alright, let's load it!
            // this is initialized on Config::init - if the global config file is found
            if (Globals::Profiles::default_name.empty())
                Globals::Profiles::default_name = Profile::profiles.front();

            Globals::Profiles::current = new Profile(Globals::Profiles::default_name);
            Globals::Profiles::current->loadSettings();
            Globals::Profiles::current->applyGraphicalSettings();

            firstGameState = new GameStateMainMenu();
        }

        // Alright, start the game!
        // This has the game loop inside.
        StateManager states;
        states.run(firstGameState, Globals::Profiles::current->getAnimation(nullptr));

        // And now the game's quitting.
        // Right before that, we must save current user's settings and set the current profile as default
        Globals::Profiles::current->save();

        SFML::exit();
    }
    catch (...)
    {
        // I dont really have a nice exception-handling scheme right
        // now. I must learn how to properly deal with them.
        SFML::exit();
        return 666;
    }

    return 0;
}

