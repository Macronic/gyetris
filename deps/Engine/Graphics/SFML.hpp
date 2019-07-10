
#include <SFML/Graphics.hpp>
#include <Engine/EngineGlobals.hpp>
#include <GUI/EventHandler.h>
#include <Engine/Graphics/Window.hpp>

#ifndef SFML_H_DEFINED
#define SFML_H_DEFINED

namespace SFML
{
    /// Initializes SFML window.
    ///
    /// The whole Engine depends on this.
    bool init();

    /// Quits SFML, destroying window
    void exit();

    /// Returns a pressed character within a
    /// timespan of #delay_ms (milliseconds).
    ///
    /// @note If you send -1, it'll block the execution,
    ///       waiting for the input indefinitely.
    ///
    /// @note It's #int because nCurses uses some other
    ///       values that don't fit on a #char variable.
    int getInput(int delay_ms=-1);

    void addEventHandler(EventHandler* handler);
    void removeEventHandler(EventHandler* handler);

    size_t getHeight();
    size_t getWidth();

    void drawTarget(std::shared_ptr<sf::Drawable> drawable);
    void display();
}

#endif //SFML_H_DEFINED

