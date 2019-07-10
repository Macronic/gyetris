#include "GameEventsManager.hpp"

namespace GameEventsManager
{
    std::map<GameEventType, std::vector<GameEventListener*>> listeners;

    void registerListener(GameEventListener* listener, GameEventType eventType)
    {
        listeners[eventType].push_back(listener);
    }

    void unregisterListener(GameEventListener* listener)
    {
        for(auto& lis : listeners)
        {
            for(size_t i = 0; i < lis.second.size(); i++)
            {
                if (lis.second[i] == listener)
                {
                    lis.second.erase(lis.second.begin() + i);
                    i--;
                }
            }
        }
    }

    void sendEvent(GameEvent event)
    {
        std::vector<GameEventListener*>& receivers = listeners[static_cast<GameEventType>(event.index())];

        for(GameEventListener* listener : receivers)
        {
            listener->handleEvent(event);
        }

    }
}
