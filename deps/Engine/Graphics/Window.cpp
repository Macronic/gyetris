#include <Engine/Graphics/Window.hpp>
#include <Engine/EngineGlobals.hpp>

#include <sstream>				// stringstream
#include <iostream>

Window::Window(int x, int y, int w, int h):
    renderTarget(nullptr),
    parent(nullptr),
    x(x),
    y(y),
    width(w),
    height(h),
    borderType(BORDER_NONE),
    topLeftTitle(""),
    topRightTitle(""),
    bottomLeftTitle(""),
    bottomRightTitle("")
{
    sf::RenderTexture* newTarget = new sf::RenderTexture;
    newTarget->create(width * EngineGlobals::Graphics::fontSize, height * EngineGlobals::Graphics::fontSize);

    this->renderTarget = newTarget;

    this->setBorders();
}

Window::Window(Window* parent, int x, int y, int width, int height):
    renderTarget(nullptr),
    borderType(BORDER_NONE),
    topLeftTitle(""),
    topRightTitle(""),
    bottomLeftTitle(""),
    bottomRightTitle("")
{
    // By sending any parameter as 0, we want it to expand
    // until possible.
    // Let's expand based if the parent window has borders
    // or not.
    if (parent->borderType == BORDER_NONE)
    {
        if (width  == 0) width  = parent->width;
        if (height == 0) height = parent->height;
    }
    else
    {
        // Has borders
        if (x == 0) x = 1;
        if (y == 0) y = 1;

        if (width  == 0) width  = parent->width  - 1;
        if (height == 0) height = parent->height - 1;
    }

    this->x = x;
    this->y = y;
    this->width  = width;
    this->height = height;

    sf::RenderTexture* newTarget = new sf::RenderTexture;
    newTarget->create(width * EngineGlobals::Graphics::fontSize, height * EngineGlobals::Graphics::fontSize);

    this->renderTarget = newTarget;
    this->parent = parent;
    this->setBorders();
}
Window::~Window()
{
    if (this->renderTarget != nullptr)
        delete renderTarget;
    renderTarget = nullptr;
}

void Window::resize(int w, int h)
{
    if (this->renderTarget != nullptr)
        delete renderTarget;

    this->width  = w;
    this->height = h;

    sf::RenderTexture* newTarget = new sf::RenderTexture;
    newTarget->create(width * EngineGlobals::Graphics::fontSize, height * EngineGlobals::Graphics::fontSize);

    this->renderTarget = newTarget;

}

void Window::print(std::string str, int x, int y, ColorPair pair)
{
    sf::Text text(str, *EngineGlobals::Graphics::font, EngineGlobals::Graphics::fontSize);
    text.setColor(sf::Color(pair.foreground.red, pair.foreground.green, pair.foreground.blue));
    text.setPosition(x * EngineGlobals::Graphics::fontSize, y * EngineGlobals::Graphics::fontSize);
    sf::RectangleShape rectangle(sf::Vector2f(str.length() * EngineGlobals::Graphics::fontSize, 1 * EngineGlobals::Graphics::fontSize));
    rectangle.setPosition(x * EngineGlobals::Graphics::fontSize, y * EngineGlobals::Graphics::fontSize);
    rectangle.setFillColor(sf::Color(pair.background.red, pair.background.green, pair.background.blue));
    renderTarget->draw(rectangle);
    renderTarget->draw(text);
}
void Window::print(std::vector<std::string> lines, int x, int y, ColorPair pair)
{
    for (size_t i = 0; i < lines.size(); i++)
        this->print(lines[i], x, y + i, pair);
}
void Window::printChar(int c, int x, int y, ColorPair pair)
{
    std::string string = "a";
    string[0] = c;
    print(string, x, y, pair);
}

void Window::draw(sf::Drawable& drawable, sf::Transformable& transformable, sf::Vector2f position)
{
    transformable.setPosition(position + sf::Vector2f(borderType == BORDER_NONE ? sf::Vector2f() : sf::Vector2f(1, 1)));
    this->renderTarget->draw(drawable);
}

void Window::draw(sf::Drawable& drawable)
{
    this->renderTarget->draw(drawable);
}

void Window::refresh()
{
    if (borderType != BORDER_NONE)
    {
        sf::RectangleShape border;
        border.setSize(sf::Vector2f(width * EngineGlobals::Graphics::fontSize-4, height * EngineGlobals::Graphics::fontSize-4));
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color(255, 255, 255, 70));
        border.setOutlineThickness(1);
        border.setPosition(2, 2);

        this->renderTarget->draw(border);
    }

    this->renderTarget->display();

    sf::Sprite sprite;
    sprite.setPosition(this->x*EngineGlobals::Graphics::fontSize, this->y*EngineGlobals::Graphics::fontSize);
    sprite.setTexture(this->renderTarget->getTexture());

    if (parent == nullptr)
    {
        SFML::drawTarget(&sprite);
    }
    else
    {
        parent->draw(sprite, sprite, sf::Vector2f(this->x*EngineGlobals::Graphics::fontSize, this->y*EngineGlobals::Graphics::fontSize));
    }

    // Previously it was:
    //
    //wrefresh(this->win);
    //
    // I've changed all calls to wrefresh() to wnoutrefresh
    // because when I have several WINDOW*, it gets heavy
    // to do the former.
    //
    // As a tradeoff, I need to call `refresh()` at the end
    // of every draw cycle.
    //
    //wnoutrefresh(this->win);
}
void Window::clear()
{
    renderTarget->clear();//werase(this->win);

    // Redrawing borders if existing
    if (this->borderType != BORDER_NONE)
        this->borders(this->borderType);

    // Now, to the titles!
    if (! this->topLeftTitle.empty())
    {
        this->print(this->topLeftTitle,
                    1, 0,
                    EngineGlobals::Theme::hilite_hilite_text);
    }
    if (! this->bottomLeftTitle.empty())
    {
        this->print(this->bottomLeftTitle,
                    0, this->getH() - 1,
                    EngineGlobals::Theme::hilite_hilite_text);
    }
    if (! this->topRightTitle.empty())
    {
        int x = (this->getW() - 1);
        int w = this->topRightTitle.size();

        this->print(this->topRightTitle,
                    x - w, 0,
                    EngineGlobals::Theme::hilite_hilite_text);
    }
    if (! this->bottomRightTitle.empty())
    {
        int x = (this->getW() - 1);
        int w = this->bottomRightTitle.size();

        this->print(this->bottomRightTitle,
                    x - w, this->getH() - 1,
                    EngineGlobals::Theme::hilite_hilite_text);
    }
}
int Window::getW() const
{
    return this->width;
}
int Window::getH() const
{
    return this->height;
}
int Window::getX() const
{
    return this->x;
}
int Window::getY() const
{
    return this->y;
}
void Window::borders(BorderType type)
{
    this->borderType = type;

    if (type == Window::BORDER_NONE)
        return;

    if (type == Window::BORDER_FANCY)
    {
        // Making shadows with Theme colors
        /* wborder(this->win,
                 ACS_VLINE    | EngineGlobals::Theme::dim_text.ncurses_pair,
                 ACS_VLINE    | EngineGlobals::Theme::dim_dim_text.ncurses_pair,
                 ACS_HLINE    | EngineGlobals::Theme::dim_text.ncurses_pair,
                 ACS_HLINE    | EngineGlobals::Theme::dim_dim_text.ncurses_pair,
                 ACS_ULCORNER | EngineGlobals::Theme::text.ncurses_pair,
                 ACS_URCORNER | EngineGlobals::Theme::dim_text.ncurses_pair,
                 ACS_LLCORNER | EngineGlobals::Theme::dim_text.ncurses_pair,
                 ACS_LRCORNER | EngineGlobals::Theme::dim_dim_text.ncurses_pair);*/
    }
    else if (type == Window::BORDER_REGULAR)
    {
        //Colors::pairActivate(this->win, EngineGlobals::Theme::dim_text);
        //wborder(this->win, '|', '|', '-', '-', '+', '+', '+', '+');
    }
}
void Window::setBorders()
{
    if (EngineGlobals::Screen::show_borders)
    {
        this->borders(EngineGlobals::Screen::fancy_borders ?
                      Window::BORDER_FANCY :
                      Window::BORDER_REGULAR);
    }
}
void Window::horizontalLine(int x, int y, int c, int width, ColorPair pair)
{
    sf::RectangleShape line(sf::Vector2f(width * EngineGlobals::Graphics::fontSize, EngineGlobals::Graphics::fontSize));
    line.setPosition(x * EngineGlobals::Graphics::fontSize, y * EngineGlobals::Graphics::fontSize);
    this->renderTarget->draw(line);
}
void Window::setTitle(std::string title, WindowTitlePosition position)
{
    switch (position)
    {
        case TOP_LEFT:
            this->topLeftTitle     = title;
            break;
        case TOP_RIGHT:
            this->topRightTitle    = title;
            break;
        case BOTTOM_LEFT:
            this->bottomLeftTitle  = title;
            break;
        case BOTTOM_RIGHT:
            this->bottomRightTitle = title;
            break;
        default:
            return;
    }
}

