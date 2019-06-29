#include <Engine/Helpers/Timer.hpp>


Timer::Timer() : started(false), paused(false) {}

void Timer::start()
{
    clock.restart();
    started = true;
    paused = false;
    timeAsPaused = sf::Time();
}

void Timer::pause()
{
    timeAsPaused = getPauseAwareTime();
    paused = true;
}

void Timer::unpause()
{
    if (!paused || !started) return;
    paused = false;
    clock.restart();
}

bool Timer::isRunning()
{
    return !paused && started;
}

bool Timer::isPaused()
{
    return paused;
}

long long int Timer::delta_us()
{
    return getPauseAwareTime().asMicroseconds();
}
long long int Timer::delta_ms()
{
    return getPauseAwareTime().asMilliseconds();
}
long long int Timer::delta_s()
{
    return static_cast<long long int>(getPauseAwareTime().asSeconds());
}

sf::Time Timer::getPauseAwareTime()
{
    if (paused)
        return timeAsPaused;

    return clock.getElapsedTime() + timeAsPaused;
}

