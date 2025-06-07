#include "event_observer.h"

extern void EventObserver_Init(event_observer_t * const obs, uint32_t num_events)
{
    ASSERT(obs != NULL);
    ASSERT(num_events > 0U );

    for(uint32_t idx = 0U; idx < num_events; idx++)
    {
        event_observer_t * observer = &obs[idx];
        for(uint32_t jdx = 0U; jdx < MAX_SUBSCRIPTIONS; jdx++)
        {
            observer->subscriber[jdx] = 0U;
        }
        observer->subscriptions = 0U;
    }
}

extern void EventObserver_Subscribe(event_observer_t * const obs, event_t event, state_t * subscriber)
{
    ASSERT( obs != NULL );
    ASSERT( subscriber != NULL );

    const uint32_t idx = (uint32_t)event;
    event_observer_t * const observer = &obs[idx];
    
    ASSERT( observer->subscriptions <= MAX_SUBSCRIPTIONS );
    /* Ensure it hasn't already been subscribed */
    for(uint32_t kdx = 0; kdx < observer->subscriptions; kdx++)
    {
        ASSERT( observer->subscriber[kdx] != subscriber );
    }

    const uint32_t jdx = observer->subscriptions;
    observer->subscriber[jdx] = subscriber;
    observer->subscriptions++;
}

extern const event_observer_t * const EventObserver_GetSubs(event_observer_t * const obs, event_t e)
{
    ASSERT( obs != NULL );
    
    const uint32_t idx = (uint32_t)e;
    const event_observer_t * const observer = &obs[idx];

    return observer;
}

