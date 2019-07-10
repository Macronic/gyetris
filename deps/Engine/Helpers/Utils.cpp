//  _________________________________________________________
// |       _        __    ___   _      _   _      __         |
// |      \ \    / / /\  | |_) | |\ | | | | |\ | / /`_       |
// |       \_\/\/ /_/--\ |_| \ |_| \| |_| |_| \| \_\_/       |
// |                                                         |
// | Adventurers, beware...                                  |
// |                                                         |
// | * The following file has lots of methods accumulated    |
// |   over the years.                                       |
// | * There isn't too much cohesion between them, so try    |
// |   to understand them individually.                      |
// |                                                         |
// |                                                         |
// | * They're mostly poor-coded, sorry 'bout that.          |
// |                                                         |
// `---------------------------------------------------------'

#include <Engine/Helpers/Utils.hpp>
#include <Engine/Helpers/String.hpp>

#include <sstream>     // sstream
#include <algorithm>   // find_if
#include <ctime>       // time()
#include <unistd.h>    // usleep()
#include <algorithm>

//  ___    __    _      ___   ___   _
// | |_)  / /\  | |\ | | | \ / / \ | |\/|
// |_| \ /_/--\ |_| \| |_|_/ \_\_/ |_|  |

std::default_random_engine Utils::Random::generator;
std::uniform_real_distribution<double> Utils::Random::distribution(0.0, 1.0);
std::random_device Utils::Random::device;

int Utils::Random::between(int min, int max)
{
    if (min > max)
        std::swap(min, max);

    return std::uniform_int_distribution(min, max)(generator);
}

double Utils::Random::between(double min, double max)
{
    if (min > max)
        std::swap(min, max);

    return (distribution(generator) * (max - min) + min);
}

bool Utils::Random::boolean()
{
    // If a random number between 0 and 9 is even
    int random_int = Utils::Random::between(0, 9);

    return ((random_int % 2) == 0);
}

bool Utils::Random::booleanWithChance(float percent)
{
    int x = Utils::Random::between(0, 99);

    return (x < (percent * 100));
}

// _____  _   _      ____
//  | |  | | | |\/| | |_
//  |_|  |_| |_|  | |_|__

void Utils::Time::delay_ms(int delay)
{
    usleep((useconds_t)delay * 100);
}


void Utils::Random::init()
{
    Utils::Random::generator = std::default_random_engine(device());
}
