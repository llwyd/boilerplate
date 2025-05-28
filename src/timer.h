#include "heap_base.h"
#include "state.h"
#include <stdint.h>
#include <stdbool.h>

#define TIMER_HEAP_LEN (32U)

typedef struct
{
    uint16_t tick;
}
timer_t;

typedef struct
{
    uint32_t key;
    event_t event;
}
timer_event_t;

typedef struct
{
    timer_event_t heap[TIMER_HEAP_LEN];
    uint32_t fill;
    uint32_t max;
}
timer_pq_t;

void Timer_Init( timer_t * const t );
void Timer_Set( timer_t * const t, uint16_t tick);
void Timer_Tick( timer_t * const t );
uint16_t Timer_Get( const timer_t * const t);



