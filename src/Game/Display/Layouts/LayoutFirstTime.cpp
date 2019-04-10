#include <Game/Display/Layouts/LayoutFirstTime.hpp>
#include <Engine/Helpers/Utils.hpp>
#include <Game/Config/Globals.hpp>

LayoutFirstTime::LayoutFirstTime(int width, int height):
    Layout(width, height)
{
    this->windowsInit();
}
LayoutFirstTime::~LayoutFirstTime()
{
    this->windowsExit();
}
void LayoutFirstTime::windowsInit()
{
    textBox.setCharacterSize(40);
    Layout::windowsInit();
}
void LayoutFirstTime::windowsExit()
{
    Layout::windowsExit();
}

std::string LayoutFirstTime::getUserName()
{
    return textBox.getText();
}

void LayoutFirstTime::draw()
{
    std::string gyetrisHello = "Hello, there!\n"
                               "It seems this is time you're running gyetris.\n"
                               "\n"
                               "Please enter a profile name.\n"
                               "For now it doesn't store anything, this screen is being shown everytime.\n"
                               "I haven't done anything with cross-platform profile management.";

    main->clear();

    textBox.update();

    sf::Vector2f textBoxPosition = sf::Vector2f((Layout::screenWidth * EngineGlobals::Graphics::fontSize - textBox.getSize().x) / 2,
                                   (Layout::screenHeight * EngineGlobals::Graphics::fontSize - 40) / 2);

    textBox.setPosition(textBoxPosition);

    sf::Text helloText;
    helloText.setString(gyetrisHello);
    helloText.setFont(*EngineGlobals::Graphics::font);

    sf::Rect<float> helloTextBounds = helloText.getLocalBounds();
    helloText.setPosition(sf::Vector2f((Layout::screenWidth * EngineGlobals::Graphics::fontSize - helloTextBounds.width) / 2, textBoxPosition.y - helloTextBounds.height - 20));

    main->draw(helloText);
    main->draw(textBox);
    main->refresh();
}

