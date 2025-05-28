#include "unity.h"
#include "heap_base.h"
#include <string.h>

typedef struct
{
    uint32_t tick;
}
timer_t;

void Timer_Init( timer_t * const t )
{
    t->tick = 0U;
}

void Timer_Set( timer_t * const t, uint32_t tick)
{
    t->tick = tick;
}

void Timer_Tick( timer_t * const t )
{
    t->tick++;
}

uint32_t Timer_Get( const timer_t * const t)
{
    return t->tick;
}

static void test_Timer_Funcs(void)
{
    timer_t timer;
    
    Timer_Init(&timer);
    TEST_ASSERT_EQUAL( 0U, Timer_Get(&timer) );

    Timer_Tick(&timer);
    TEST_ASSERT_EQUAL( 1U, Timer_Get(&timer) );
    
    Timer_Set(&timer, UINT32_MAX);
    TEST_ASSERT_EQUAL( UINT32_MAX, Timer_Get(&timer) );
    
    Timer_Tick(&timer);
    TEST_ASSERT_EQUAL( 0U, Timer_Get(&timer) );
}

extern void TimerTestSuite(void)
{
    RUN_TEST(test_Timer_Funcs);
}
