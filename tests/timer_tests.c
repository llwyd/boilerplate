#include "unity.h"
#include "heap_base.h"
#include "timer.h"
#include <string.h>

static void test_Timer_Funcs(void)
{
    timer_t timer;
    
    Timer_Init(&timer);
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
    heap_t heap;
    
    Timer_Init(&timer);
    Heap_Init(&heap);
    
    TEST_ASSERT_EQUAL( 0U, heap.fill );
}

extern void TimerTestSuite(void)
{
    RUN_TEST(test_Timer_Funcs);
    RUN_TEST(test_Timer_EnQEvent);
}
