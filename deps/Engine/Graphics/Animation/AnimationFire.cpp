#include <Engine/Graphics/Animation/AnimationFire.hpp>
#include <Engine/Graphics/Colors.hpp>
#include <Engine/Helpers/Utils.hpp>

static ColorPair red        = Colors::pair("red", "default");
static ColorPair redBold    = Colors::pair("red", "default", true);
static ColorPair white;
static ColorPair yellow     = Colors::pair("yellow", "default");
static ColorPair yellowBold = Colors::pair("yellow", "default", true);

// An ASCII gray scale :)
// Characters will be accessed proportionally to the intensity
// int gray_scale_size = 70;
// char gray_scale[71] = ".\'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$ ";

static int gray_scale_size = 12;
static char gray_scale[13] = " .':-=+*#%@#";
static int intensity_normal = 13;
static int intensity_more = 20;
static int clearDelay = 5;

AnimationFire::AnimationFire(Window* window):
    AnimationLegacy(window),
    particle(NULL),
    burstTimeLeft(0),
    played(false)
{ }
AnimationFire::~AnimationFire()
{
    SAFE_DELETE(particle)
}
void AnimationFire::load()
{
    unsigned int width  = window->getW();
    unsigned int height = window->getH();


    particle = new Array2D<ParticleFire>(width, height);

    // Creating the cooling map
    coolingMap = new Array2D<int>(width, height);

    if (width > 0 && height > 0)
    {
        for (unsigned int i = 0; i < width; i++)
            for (unsigned int j = 0; j < height; j++)
                coolingMap->set(i, j, Utils::Random::between(INTENSITY_MIN,
                                INTENSITY_PERCENT(intensity_normal)));

        // Will smooth the cooling map a number of times
        for (int n = 0; n < 10; n++)
            for (unsigned int i = 1; i < width-1; i++)
                for (unsigned int j = 1; j < height-1; j++)
                    coolingMap->set(i, j, (coolingMap->at(i-1, j) +
                                           coolingMap->at(i+1, j) +
                                           coolingMap->at(i, j+1) +
                                           coolingMap->at(i, j-1)) / 4);
    }


    GameEventsManager::registerListener(this, GameEventType::CLEAR_LINES_EVENT);
    GameEventsManager::registerListener(this, GameEventType::HEIGHT_CHANGED_EVENT);
    GameEventsManager::registerListener(this, GameEventType::START_GAME_EVENT);
    GameEventsManager::registerListener(this, GameEventType::STOP_GAME_EVENT);

    currentLineHeight = 0;

    timer.start();
    AnimationLegacy::load();
}

void AnimationFire::update()
{
    // Updating only at the right time!
    if (timer.delta_ms() < 100)
        return;

    // How fast the fire cools down each frame
    double cooling_ratio = INTENSITY_PERCENT(Utils::Random::between(0., 10.) + (10 - currentLineHeight * 0.5));

    if (burstTimeLeft > 0)
    {
        cooling_ratio *= 0.3;
        burstTimeLeft--;
    }

    if (played == false)
    {
        cooling_ratio = 7;
    }

// Spawning high-intensity flames on the bottom particles
    for (unsigned int i = 0; i < (particle->width()); i++)
        particle->set(i, particle->height() - 1, ParticleFire(Utils::Random::between(INTENSITY_PERCENT(90), INTENSITY_MAX)));

    // Randomly adding Sparks - high-intensity flames little higher
    for (unsigned int i = 0; i < (particle->width()); i++)
    {
        if (Utils::Random::booleanWithChance(2.31))
        {
            int height = particle->height() - Utils::Random::between(3, 6);

            particle->set(i, height, ParticleFire(Utils::Random::between(INTENSITY_PERCENT(90), INTENSITY_MAX)));
        }
    }

    // Making all particles climb up
    for (unsigned int i = 0; i < (particle->width()); i++)
    {
        for (unsigned int j = 0; j < (particle->height()-1); j++)
        {
            // Cooling all particles based on the ones below
            particle->set(i, j, ParticleFire(particle->at(i, j + 1).intensity - cooling_ratio));

            // Cooling based on the cooling map
            particle->set(i, j, ParticleFire(particle->at(i, j).intensity - coolingMap->at(i, j)));
        }
    }

    timer.start();
    AnimationLegacy::update();
}
void AnimationFire::draw()
{
    for (unsigned int i = 0; i < (particle->width()); i++)
    {
        for (unsigned int j = 0; j < (particle->height()); j++)
        {
            int       c = ' ';
            ColorPair p = white;
            int       s = particle->at(i, j).intensity;

            if (s > INTENSITY_PERCENT(90))
                p = white;

            else if (s > INTENSITY_PERCENT(80))
                p = yellowBold;

            else if (s > INTENSITY_PERCENT(70))
                p = yellowBold;

            else if (s > INTENSITY_PERCENT(60))
                p = yellow;

            else if (s > INTENSITY_PERCENT(50))
                p = redBold;

            else if (s > INTENSITY_PERCENT(40))
                p = redBold;

            else if (s > INTENSITY_PERCENT(30))
                p = red;

            else if (s > INTENSITY_PERCENT(20))
                p = red;

            else
                continue; // Too low intensity


            if ((s > INTENSITY_MAX) || (s < INTENSITY_MIN))
                continue;

            else
                c = gray_scale[(int)((s - INTENSITY_MIN) * (gray_scale_size-1)/INTENSITY_MAX)];

            print(std::string(1, (char)c), i, j, p.foreground);
        }
    }
    AnimationLegacy::draw();
}


void AnimationFire::handleEvent(GameEvent event)
{
    switch(event.index())
    {
        case GameEventType::CLEAR_LINES_EVENT:
            burstTimeLeft = std::get<GameEventType::CLEAR_LINES_EVENT>(event) * std::get<GameEventType::CLEAR_LINES_EVENT>(event) / 5 * clearDelay;
            break;
        case GameEventType::HEIGHT_CHANGED_EVENT:
            currentLineHeight = std::get<GameEventType::HEIGHT_CHANGED_EVENT>(event);
            break;
        case GameEventType::START_GAME_EVENT:
            played = true;
            break;
        case GameEventType::STOP_GAME_EVENT:
            played = false;
            break;
        default:
            break;
    }
}
