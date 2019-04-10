#ifndef LAYOUTFIRSTTIME_H_DEFINED
#define LAYOUTFIRSTTIME_H_DEFINED

#include <Engine/Graphics/Layout.hpp>
#include <Engine/Graphics/Window.hpp>
#include <Engine/Graphics/Widgets/Menu.hpp>
#include <GUI/ArcadeTextBox.h>
/// How we show the screen at GameStateFirstTime.
/// See it's documentation there.
class LayoutFirstTime: public Layout
{

    ArcadeTextBox textBox;

  public:
    LayoutFirstTime(int width, int height);
    virtual ~LayoutFirstTime();

    void windowsInit();
    void windowsExit();

    std::string getUserName();

    void draw();
};

#endif //LAYOUTFIRSTTIME_H_DEFINED
