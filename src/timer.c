#include "timer.h"

void Timer_Init( timer_t * const t )
{
    t->tick = 0U;
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
