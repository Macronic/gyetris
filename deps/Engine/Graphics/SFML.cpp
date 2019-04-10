#include <Engine/Graphics/SFML.hpp>
#include <iostream>
#include <GUI/EventHandler.h>

namespace SFML
{
    sf::RenderWindow* window = nullptr;
    bool wasSomethingDrawn = false;

    std::vector<EventHandler*> handlers;
    bool init()
    {
        if (SFML::window != nullptr)
            delete SFML::window;

        SFML::window = new sf::RenderWindow;
        SFML::window->create(sf::VideoMode(80 * EngineGlobals::Graphics::fontSize, 30 * EngineGlobals::Graphics::fontSize), "gyetris");

        return true;
    }

    void exit()
    {
        if (SFML::window != nullptr)
        {
            SFML::window->close();

            delete SFML::window;
            SFML::window = nullptr;
        }
    }

    int getInput(int delay_ms)
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            bool handled = false;
            for (EventHandler* handler : handlers)
            {
                if(handler->handleEvent(event))
                {
                    handled = true;
                    break;
                }
            }

            if (handled)
                continue;

            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    exit();
                    break;

                case sf::Event::KeyPressed:
                    return event.key.code;
                    break;
            }
        }

        return -1;
    }


    size_t getWidth()
    {
        if (window == nullptr)
            return 0;
        return window->getSize().x / EngineGlobals::Graphics::fontSize;
    }


    size_t getHeight()
    {
        if (window == nullptr)
            return 0;
        return window->getSize().y / EngineGlobals::Graphics::fontSize;
    }

    void drawTarget(sf::Drawable* drawable)
    {
        if (window == nullptr)
            return;

        window->draw(*drawable);
        wasSomethingDrawn = true;
    }

    void display()
    {
        if (wasSomethingDrawn)
        {
            if (window == nullptr)
                return;

            window->display();
            wasSomethingDrawn = false;
            window->clear();
        }

    }

    void addEventHandler(EventHandler* handler)
    {
        if (handler == nullptr)
            return;

        for (EventHandler* oldHandler : handlers)
        {
            if (handler == oldHandler)
                return;
        }

        handlers.push_back(handler);
    }

    void removeEventHandler(EventHandler* handler)
    {
        if (handler == nullptr)
            return;

        for (size_t i = 0; i < handlers.size(); i++)
        {
            if (handler == handlers[i])
            {
                handlers.erase(handlers.begin() + i);
                i--;
            }
        }
    }

}
