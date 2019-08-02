#include <Engine/Graphics/SFML.hpp>
#include <iostream>
#include <GUI/EventHandler.h>
#include <Game/Config/Globals.hpp>

namespace SFML
{
    sf::RenderWindow* window = nullptr;
    bool wasSomethingDrawn = false;
    sf::Text text;
    std::vector<EventHandler*> handlers;

    DrawQueue queue;

    bool init()
    {
        if (SFML::window != nullptr)
            delete SFML::window;

        SFML::window = new sf::RenderWindow;
        SFML::window->create(sf::VideoMode(80 * EngineGlobals::Graphics::fontSize, 40 * EngineGlobals::Graphics::fontSize), "gyetris");
        SFML::window->setFramerateLimit(60);

        text = sf::Text("", *EngineGlobals::Graphics::font, EngineGlobals::Graphics::fontSize);
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

        while (window != nullptr && window->pollEvent(event))
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
                    exit();
                    Globals::save();
                    std::exit(0);
                    break;
                case sf::Event::Resized:
                    window->setSize(sf::Vector2u(event.size.width, event.size.height));
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

    void drawTarget(std::shared_ptr<sf::Drawable> drawable)
    {
        queue.add(drawable);
        if (window == nullptr)
            return;

        wasSomethingDrawn = true;
    }

    void display()
    {
        if (wasSomethingDrawn)
        {
            if (window == nullptr)
                return;

            window->draw(queue);
            queue.clear();
            window->display();
            wasSomethingDrawn = false;
            window->clear(sf::Color::Black);
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

    void printStringOn(std::string string, size_t x, size_t y, sf::RenderTarget& target, sf::Color color)
    {
        text.setString(string);
        text.setFillColor(color);
        text.setPosition(x * EngineGlobals::Graphics::fontSize, y * EngineGlobals::Graphics::fontSize);

        target.draw(text);
    }
}
