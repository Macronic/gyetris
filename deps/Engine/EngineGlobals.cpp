#include <Engine/EngineGlobals.hpp>

// Defining `extern` variables
bool EngineGlobals::Screen::center_horizontally;
bool EngineGlobals::Screen::center_vertically;
bool EngineGlobals::Screen::show_borders;
bool EngineGlobals::Screen::fancy_borders;
bool EngineGlobals::Screen::outer_border;

ColorPair EngineGlobals::Theme::text;
ColorPair EngineGlobals::Theme::hilite_text;
ColorPair EngineGlobals::Theme::hilite_hilite_text;
ColorPair EngineGlobals::Theme::dim_text;
ColorPair EngineGlobals::Theme::dim_dim_text;
ColorPair EngineGlobals::Theme::textbox;

sf::Font* EngineGlobals::Graphics::font = nullptr;
int EngineGlobals::Graphics::fontSize = 20;

void EngineGlobals::init()
{
    if (EngineGlobals::Graphics::font != nullptr)
        delete EngineGlobals::Graphics::font;
    EngineGlobals::Graphics::font = new sf::Font;
    EngineGlobals::Graphics::font->loadFromFile("VCR_OSD_MONO_1.001.ttf");

    EngineGlobals::Screen::center_horizontally = false;
    EngineGlobals::Screen::center_vertically   = false;

    EngineGlobals::Screen::show_borders  = true;
    EngineGlobals::Screen::fancy_borders = true;
    EngineGlobals::Screen::outer_border  = true;

    EngineGlobals::Theme::text               = Colors::pair("white",   "default", true);
    EngineGlobals::Theme::hilite_text        = Colors::pair("cyan",    "default");
    EngineGlobals::Theme::hilite_hilite_text = Colors::pair("cyan",    "default", true);
    EngineGlobals::Theme::dim_text           = Colors::pair("black",   "default", true);
    EngineGlobals::Theme::dim_dim_text       = Colors::pair("black",   "default");
    EngineGlobals::Theme::textbox            = Colors::pair("white",   "cyan");
}

