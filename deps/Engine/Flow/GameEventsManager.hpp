#include <string>
#include <map>
#include <vector>
#include <variant>

#ifndef GAMEEVENTSMANAGER_H
#define GAMEEVENTSMANAGER_H

typedef std::variant<size_t, std::monostate, std::monostate, std::monostate, size_t> GameEvent;

enum GameEventType
{
    CLEAR_LINES_EVENT,
    START_GAME_EVENT,
    STOP_GAME_EVENT,
    CLEAR_SCREEN_EVENT,
    HEIGHT_CHANGED_EVENT
};

class GameEventListener;

namespace GameEventsManager
{
    extern std::map<GameEventType, std::vector<GameEventListener*>> listeners;

    void registerListener(GameEventListener* listener, GameEventType eventType);
    void unregisterListener(GameEventListener* listener);

    void sendEvent(GameEvent event);
};

class GameEventListener
{
  public:
    virtual ~GameEventListener()
    {
        GameEventsManager::unregisterListener(this);
    }

    virtual void handleEvent(GameEvent event) = 0;
};

#endif // GAMEEVENTSMANAGER_H
