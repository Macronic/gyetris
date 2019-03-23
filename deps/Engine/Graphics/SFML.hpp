
#include <SFML/Graphics.hpp>
#include <Engine/EngineGlobals.hpp>

#ifndef SFML_H_DEFINED
#define SFML_H_DEFINED

namespace SFML
{
    /// Initializes Ncurses mode.
    ///
    /// The whole Engine depends on this.
    bool init();

    /// Quits Ncurses mode.
    ///
    /// Make sure to call it at the end of the game,
    /// otherwise the terminal will be left at a
    /// strange state.
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

    size_t getHeight();
    size_t getWidth();

    void drawTarget(sf::Drawable* drawable);
    void display();
}

#endif //SFML_H_DEFINED

