#include "EventHandler.h"

#include <Engine/Graphics/SFML.hpp>

EventHandler::EventHandler()
{
    link();
}

EventHandler::~EventHandler()
{
    unlink();
}

void EventHandler::unlink()
{
    SFML::removeEventHandler(this);
}

void EventHandler::link()
{
    SFML::addEventHandler(this);
}
