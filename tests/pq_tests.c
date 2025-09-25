#include "unity.h"
#include "pq_base.h"
#include <string.h>

typedef struct
{
    pq_key_t key;
    uint32_t data;
}
pq_test_t;

static void test_PQ_Init(void)
{
    pq_t pq;
    pq_test_t pool[PQ_FULL_LEN];
    uint8_t bytes = sizeof(pq_test_t); 
    
    PQ_Init(&pq, &pool->key, bytes);
    
    TEST_ASSERT_EQUAL( 0U, pq.fill );
    TEST_ASSERT_EQUAL( PQ_DEFAULT_LEN, pq.max );

    for(uint32_t idx = 0; idx < PQ_FULL_LEN; idx++)
    {
        TEST_ASSERT_EQUAL(&pool[idx].key, pq.heap[idx]);
        TEST_ASSERT_EQUAL(UINT32_MAX, pool[idx].key.key);
    }
}

extern void PQTestSuite(void)
{
    RUN_TEST(test_PQ_Init);
}
