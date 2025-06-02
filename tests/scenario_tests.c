#include "emitter_tests.h"
#include "scenario_tests.h"
#include "emitter_base.h"
#include "state.h"
#include "fifo_base.h"
#include "event_heap.h"
#include "unity.h"
#include <string.h>

#define EVENTS(EVNT) \
    EVNT(TestEvent0) \
    EVNT(TestEvent1) \
    EVNT(TestEvent2) \

GENERATE_EVENTS( EVENTS );

static void EnqueueEventAfter(heap_t * heap, event_t e, uint32_t time_ms)
{
    heap_data_t data =
    {
        .key = time_ms,
        .event = e,
    };

    Heap_Push(heap, data);
}

void test_Scenario_EventPriority0(void)
{
    heap_t heap;
    Heap_Init(&heap);

    TEST_ASSERT_TRUE(Heap_IsEmpty(&heap));

    EnqueueEventAfter(&heap, EVENT(TestEvent0), 1000U);
    EnqueueEventAfter(&heap, EVENT(TestEvent1), 250U);
    EnqueueEventAfter(&heap, EVENT(TestEvent2), 500U);

    heap_data_t out = Heap_PopFull(&heap);
    TEST_ASSERT_EQUAL(250U, out.key);
    TEST_ASSERT_EQUAL(EVENT(TestEvent1), out.event);
    
    out = Heap_PopFull(&heap);
    TEST_ASSERT_EQUAL(500U, out.key);
    TEST_ASSERT_EQUAL(EVENT(TestEvent2), out.event);
    
    out = Heap_PopFull(&heap);
    TEST_ASSERT_EQUAL(1000U, out.key);
    TEST_ASSERT_EQUAL(EVENT(TestEvent0), out.event);
}

extern void SCENARIOTestSuite(void)
{
    RUN_TEST(test_Scenario_EventPriority0);
}

