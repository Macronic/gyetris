#include <Engine/InputManager.hpp>
#include <Engine/Graphics/SFML.hpp>

int InputManager::pressedKey = -1; // Starting with blank value
std::map<std::string, int> InputManager::binds;

void InputManager::bind(std::string name, int key)
{
    if (name.empty() || key == -1)
        return;

    InputManager::binds[name] = key;
}

void InputManager::unbind(std::string name)
{
    InputManager::binds.erase(name);
}

bool InputManager::exists(std::string key)
{
    return (InputManager::binds.find(key) != InputManager::binds.end());
}

bool InputManager::isBound(int key)
{
    if (InputManager::binds.empty())
        return false;
    // C++11 compatibility!
    // I wish I could use `auto` :(
    for (std::map<std::string, int>::iterator it = InputManager::binds.begin();
            it != InputManager::binds.end();
            ++it)
    {
        if (it->second == key)
            return true;
    }
    return false;
}

int InputManager::getBind(std::string name)
{
    // If #key is not binded to anything...
    if (InputManager::binds.find(name) == InputManager::binds.end())
        return -1;

    return (InputManager::binds[name]);
}
void InputManager::update(int delay_ms)
{
    InputManager::pressedKey = SFML::getInput(delay_ms);
}

bool InputManager::noKeyPressed()
{
    return (InputManager::pressedKey == -1);
}

bool InputManager::isPressed(int key)
{
    return (InputManager::pressedKey == key);
}

bool InputManager::isPressed(std::string key)
{
    // If #key is not binded to anything, will return false
    if (InputManager::binds.find(key) == InputManager::binds.end())
        return false;

    return (InputManager::isPressed(InputManager::binds[key]));
}

std::string InputManager::keyToString(int value)
{
    // Is character inside the ASCII table?
    if (value >= 0 && value <= 127)
    {
        if (value == ' ')
            return "space";

        // The "printable" part of the ASCII table - easy
        if (value > ' ' && value <=  '~')
        {
            // Converting (int -> char -> char* -> std::string)
            char c[2] = { (char)value, '\0' };

            return std::string(c);
        }

        // Non-printable, then...
        // Let's get some names
        switch (value)
        {
            case 0:
                return "null";
            case 27:
                return "escape";
            case 127:
                return "delete";
        }
    }

    // If not, then this character is a special Ncurses value.
    // Those things were directy taken from <ncurses.h>
    //
    // NOTE: Wont use KEY_BREAK, KEY_SRESET, KEY_RESET, KEY_F0
    //       and KEY_EIC beucase they're strange..
    // NOTE: Also not using KEY_MOUSE, KEY_RESIZE and KEY_EVENT
    //       because they're Ncurses' flags for other things
    //       than the keyboard.
    //
    switch (value)
    {

        default:
            break;
    }
    return "undefined";
}

int InputManager::stringToKey(std::string string)
{
    if (string == "space")
        return sf::Keyboard::Space;

    return -1;
}

