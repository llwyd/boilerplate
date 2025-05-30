#include "timer.h"

static void swap( timer_event_t * a, timer_event_t * b )
{
    assert(a != NULL);
    assert(b != NULL);

    timer_event_t temp = *a;
    *a = *b;
    *b = temp;
}

void Timer_Enqueue(timer_pq_t * const q, event_t * evnt, uint16_t time_ms)
{

}

void Timer_Init( timer_t * const t, timer_pq_t * const q )
{
    t->tick = 0U;
    if(q != NULL)
    {
        q->fill = 0U;
        q->max = TIMER_HEAP_LEN;
        for(uint32_t idx = 0U; idx < TIMER_HEAP_LEN; idx++)
        {
            q->heap[idx].key = 0xFFFF;
        }
    }
}

void Timer_Set( timer_t * const t, uint16_t tick)
{
    t->tick = tick;
}

void Timer_Tick( timer_t * const t )
{
    t->tick++;
}

uint16_t Timer_Get( const timer_t * const t)
{
    return t->tick;
}


