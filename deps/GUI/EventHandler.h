#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <SFML/Graphics.hpp>

class EventHandler
{

protected:
    EventHandler();
    ~EventHandler();

public:
    virtual bool handleEvent(sf::Event event) = 0;
    void unlink();
    void link();
};

#endif // EVENTHANDLER_H
