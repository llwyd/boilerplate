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
   
    for(uint32_t idx = 0; idx < PQ_FULL_LEN; idx++)
    {
        pool[idx].data = 0x12345678;
    }

    PQ_Init(&pq, &pool->key, bytes);
   
    TEST_ASSERT_TRUE( PQ_IsEmpty(&pq));
    TEST_ASSERT_EQUAL( 0U, pq.fill );
    TEST_ASSERT_EQUAL( PQ_DEFAULT_LEN, pq.max );

    for(uint32_t idx = 0; idx < PQ_FULL_LEN; idx++)
    {
        TEST_ASSERT_EQUAL(&pool[idx].key, pq.heap[idx]);
        TEST_ASSERT_EQUAL(UINT32_MAX, pool[idx].key.key);
        TEST_ASSERT_EQUAL(0x12345678, pool[idx].data);
    }
}

static void test_PQ_Push(void)
{
    pq_t pq;
    pq_test_t pool[PQ_FULL_LEN];
    uint8_t bytes = sizeof(pq_test_t); 
   
    for(uint32_t idx = 0; idx < PQ_FULL_LEN; idx++)
    {
        pool[idx].data = 0x12345678;
    }

    PQ_Init(&pq, &pool->key, bytes);
   
    TEST_ASSERT_TRUE( PQ_IsEmpty(&pq));
    TEST_ASSERT_EQUAL( 0U, pq.fill );
    TEST_ASSERT_EQUAL( PQ_DEFAULT_LEN, pq.max );

    pq_test_t * ptr = (pq_test_t *)PQ_Push(&pq, 0xaaaa);
    ptr->data = 0x5555;
    TEST_ASSERT_FALSE( PQ_IsEmpty(&pq));
    TEST_ASSERT_EQUAL( 1U, pq.fill );
    TEST_ASSERT_EQUAL( 0xaaaa, ptr->key.key );
    TEST_ASSERT_EQUAL( 0x5555, ptr->data );

    TEST_ASSERT_EQUAL( 0xaaaa, pq.heap[0]->key );
    TEST_ASSERT_EQUAL( 0x5555, ((pq_test_t *)pq.heap[0])->data );
    
    ptr = (pq_test_t *)PQ_Push(&pq, 0x1111);
    ptr->data = 0x2222;
    
    TEST_ASSERT_EQUAL( 2U, pq.fill );
    TEST_ASSERT_EQUAL( 0x1111, ptr->key.key );
    TEST_ASSERT_EQUAL( 0x2222, ptr->data );
    
    TEST_ASSERT_EQUAL( 0x1111, pq.heap[0]->key );
    TEST_ASSERT_EQUAL( 0x2222, ((pq_test_t *)pq.heap[0])->data );
    
    TEST_ASSERT_EQUAL( 0xaaaa, pq.heap[1]->key );
    TEST_ASSERT_EQUAL( 0x5555, ((pq_test_t *)pq.heap[1])->data );
}

static void test_PQ_Peek(void)
{
    pq_t pq;
    pq_test_t pool[PQ_FULL_LEN];
    uint8_t bytes = sizeof(pq_test_t); 

    PQ_Init(&pq, &pool->key, bytes);

    (void)PQ_Push(&pq, 0x1234);
    (void)PQ_Push(&pq, 0x4345);
    (void)PQ_Push(&pq, 0x0666);
    (void)PQ_Push(&pq, 0x1066);
    
    TEST_ASSERT_EQUAL( 4U, pq.fill );
    pq_test_t * ptr = (pq_test_t *)PQ_Peek(&pq, 0u);

    TEST_ASSERT_EQUAL(ptr->key.key, 0x0666);
    TEST_ASSERT_EQUAL( 4U, pq.fill );
}

static void test_PQ_Pop(void)
{
    pq_t pq;
    pq_test_t pool[PQ_FULL_LEN];
    uint8_t bytes = sizeof(pq_test_t); 

    PQ_Init(&pq, &pool->key, bytes);

    (void)PQ_Push(&pq, 0x1234);
    (void)PQ_Push(&pq, 0x4345);
    (void)PQ_Push(&pq, 0x0666);
    (void)PQ_Push(&pq, 0x1066);
    
    TEST_ASSERT_EQUAL( 4U, pq.fill );
    pq_test_t * ptr = (pq_test_t *)PQ_Pop(&pq);

    TEST_ASSERT_EQUAL(ptr->key.key, 0x0666);
    TEST_ASSERT_EQUAL( 3U, pq.fill );
    
    ptr = (pq_test_t *)PQ_Pop(&pq);
    TEST_ASSERT_EQUAL(ptr->key.key, 0x1066);
    TEST_ASSERT_EQUAL( 2U, pq.fill );
    
    ptr = (pq_test_t *)PQ_Pop(&pq);
    TEST_ASSERT_EQUAL(ptr->key.key, 0x1234);
    TEST_ASSERT_EQUAL( 1U, pq.fill );
    
    ptr = (pq_test_t *)PQ_Pop(&pq);
    TEST_ASSERT_EQUAL(ptr->key.key, 0x4345);
    TEST_ASSERT_EQUAL( 0U, pq.fill );
}

static void test_PQ_DecreaseKey(void)
{
    pq_t pq;
    pq_test_t pool[PQ_FULL_LEN];
    uint8_t bytes = sizeof(pq_test_t); 

    PQ_Init(&pq, &pool->key, bytes);

    pq_test_t * ptr = (pq_test_t*)PQ_Push(&pq, 0x1234);
    ptr = (pq_test_t*)PQ_Push(&pq, 0x4345);
    ptr->data = 0x4444;
    ptr = (pq_test_t*)PQ_Push(&pq, 0x0666);
    ptr->data = 0x5555;
    ptr = (pq_test_t*)PQ_Push(&pq, 0x1066);
    
    TEST_ASSERT_EQUAL( 4U, pq.fill );

    ptr = (pq_test_t*)PQ_Peek(&pq, 0u);
    TEST_ASSERT_EQUAL(ptr->key.key, 0x0666);
    TEST_ASSERT_EQUAL(ptr->data, 0x5555);
    
    ptr = (pq_test_t*)PQ_DecreaseKey(&pq, 3u, 0x0);

    TEST_ASSERT_EQUAL(ptr->key.key, 0x0);
    TEST_ASSERT_EQUAL(ptr->data, 0x4444);
    
    ptr = (pq_test_t*)PQ_Peek(&pq, 0u);
    TEST_ASSERT_EQUAL(ptr->key.key, 0x0);
    TEST_ASSERT_EQUAL(ptr->data, 0x4444);
}

extern void PQTestSuite(void)
{
    RUN_TEST(test_PQ_Init);
    RUN_TEST(test_PQ_Push);
    RUN_TEST(test_PQ_Peek);
    RUN_TEST(test_PQ_Pop);
    RUN_TEST(test_PQ_DecreaseKey);
}
