#include "unity.h"
#include "heap_base.h"
#include "timer.h"
#include <string.h>

#define EVENTS(EVNT) \
    EVNT(TestEvent0) \
    EVNT(TestEvent1) \
    EVNT(TestEvent2) \

static void test_Timer_Funcs(void)
{
    timer_t timer;
    
    Timer_Init(&timer, NULL);
    TEST_ASSERT_EQUAL( 0U, Timer_Get(&timer) );

    Timer_Tick(&timer);
    TEST_ASSERT_EQUAL( 1U, Timer_Get(&timer) );
    
    Timer_Set(&timer, UINT16_MAX);
    TEST_ASSERT_EQUAL( UINT16_MAX, Timer_Get(&timer) );
    
    Timer_Tick(&timer);
    TEST_ASSERT_EQUAL( 0U, Timer_Get(&timer) );
}


static void test_Timer_EnQEvent(void)
{
    timer_t timer;
    timer_pq_t q;
    
    Timer_Init(&timer, &q);
    
    TEST_ASSERT_EQUAL( 0U, q.fill );
    TEST_ASSERT_EQUAL( TIMER_HEAP_LEN, q.max );
}

extern void TimerTestSuite(void)
{
    RUN_TEST(test_Timer_Funcs);
    RUN_TEST(test_Timer_EnQEvent);
}
