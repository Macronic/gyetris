#include <Engine/Graphics/Colors.hpp>

#include <cstdlib>				// strtol()

// Single Color

Color::Color(std::string name):
    name(name),
    red(0),
    green(0),
    blue(0)
{ }

std::string Color::toString()
{
    if (! this->name.empty())
        return this->name;

    return (Utils::String::toString(this->red) + "," +
            Utils::String::toString(this->green) + "," +
            Utils::String::toString(this->blue));
}

Color::operator sf::Color()
{
    return sf::Color(red, green, blue);
}

Color Color::fromString(std::string str)
{
    if (str.find(",") == std::string::npos)
    {
        // Format is "name"
        return Colors::name(str);
    }
    else
    {
        // Format "red,green,blue"
        std::vector<std::string> v = Utils::String::split(str, ',');
        if (v.size() != 3)
            return Color();

        for (size_t i = 0; i < v.size(); ++i)
            v[i] = Utils::String::trim(v[i]);

        int red   = Utils::String::to<int>(v[0]);
        int green = Utils::String::to<int>(v[1]);
        int blue  = Utils::String::to<int>(v[2]);

        return Colors::rgb(red, green, blue);
    }
}


// Color Pair


ColorPair::ColorPair():
    foreground(Colors::name("white")),
    background(Colors::name("default")),
    bold(false)
{ }

ColorPair::ColorPair(Color foreground, Color background):
    foreground(foreground),
    background(background),
    bold(false)
{ }

ColorPair ColorPair::reverse()
{
    return Colors::pair(background, foreground);
}

std::string ColorPair::toString()
{
    std::string bold = (this->bold ?
                        "!" :
                        "");

    return (foreground.toString() + "+" + background.toString() + bold);
}

ColorPair ColorPair::fromString(std::string str)
{
    bool is_bold = false;

    size_t pos = str.find("!");
    if (pos != std::string::npos)
    {
        is_bold = true;
        str.erase(pos, 1);
    }

    std::vector<std::string> v = Utils::String::split(str, '+');

    if (v.size() != 2)
        return ColorPair();

    Color fg = Color::fromString(v[0]);
    Color bg = Color::fromString(v[1]);

    return Colors::pair(fg, bg, is_bold);
}

// All Colors

bool Colors::hasColors = false;

bool Colors::init()
{
    return false;
    //There are no colors in SFML version for now.
}

Color Colors::rgb(short red, short green, short blue)
{
    Color color;
    color.name = ""; // since it's RGB

    static int color_no = 8;
    color_no++;
    // `init_color` receives values from 0 to 1000,
    // so we'll map from 255 to 1000
    int expand = 1000/255;

    color.ncurses_color = (color_no - 1);

    color.red   = red;
    color.green = green;
    color.blue  = blue;
    return color;
}

Color Colors::hex(std::string hex)
{
    Color color;

    if ((hex[0]     != '#') || // sorry
            (hex.size() != 7)) // #RRGGBB format
        return color;

    char col[3];
    col[2] = '\0';

    col[0] = hex[1];
    col[1] = hex[2];
    long r = strtol(col, nullptr, 16);

    col[0] = hex[3];
    col[1] = hex[4];
    long g = strtol(col, nullptr, 16);

    col[0] = hex[5];
    col[1] = hex[6];
    long b = strtol(col, nullptr, 16);
    return Colors::rgb(r, g, b);
}

ColorPair Colors::pair(Color& foreground, Color& background, bool is_bold)
{
    ColorPair pair(foreground, background);

    if (is_bold)
        pair.bold = true;

    return pair;
}
Color Colors::name(std::string str)
{
    Color color;

    if (str.empty())
        return color;

    if (str == "default")      color = Colors::rgb(0, 0, 0);
    else if (str == "black")   color = Colors::rgb(0, 0, 0);
    else if (str == "red")     color = Colors::rgb(190, 40, 40);
    else if (str == "green")   color = Colors::rgb(40, 190, 40);
    else if (str == "yellow")  color = Colors::rgb(190, 190, 40);
    else if (str == "blue")    color = Colors::rgb(40, 40, 190);
    else if (str == "magenta") color = Colors::rgb(190, 40, 190);
    else if (str == "cyan")    color = Colors::rgb(40, 190, 190);
    else if (str == "white")   color = Colors::rgb(255, 255, 255);

    color.name = str;
    return color;
}

ColorPair Colors::pair(std::string foreground, std::string background, bool is_bold)
{
    if (foreground.empty() || background.empty())
        return ColorPair();

    Color f = Colors::name(foreground);
    Color b = Colors::name(background);

    return Colors::pair(f, b, is_bold);
}
