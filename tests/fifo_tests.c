#include "fifo_tests.h"
#include "fifo_base.h"
//#include "fifo.h"
#include "unity.h"
#include <string.h>

//CREATE_FIFO(UInt32,test_fifo_t, uint32_t, 32 );

#define FIFO_LEN (32U)
typedef struct
{
    fifo_base_t base;
    uint32_t queue[FIFO_LEN];
    uint32_t data;
} test_fifo_t;

void Enqueue( fifo_base_t * const fifo );
void Dequeue( fifo_base_t * const fifo );
void Flush( fifo_base_t * const fifo );

void Init( test_fifo_t * fifo )
{
    static const fifo_vfunc_t vfunc =
    {
        .enq = Enqueue,
        .deq = Dequeue,
        .flush = Flush,
    };
    FIFO_Init( (fifo_base_t *)fifo, FIFO_LEN );
    
    fifo->base.vfunc = &vfunc;
    fifo->data = 0x0;
    memset(fifo->queue, 0x00, FIFO_LEN * sizeof(fifo->data));
}

void Enqueue( fifo_base_t * const base )
{
    assert(base != NULL );
    test_fifo_t * fifo = (test_fifo_t *)base;

    fifo->queue[ fifo->base.write_index ] = fifo->data;
    fifo->base.write_index++;
    fifo->base.fill++;
    fifo->base.write_index = ( fifo->base.write_index & ( fifo->base.max - 1U ) );
}

void Dequeue( fifo_base_t * const base )
{
    assert(base != NULL );
    test_fifo_t * fifo = (test_fifo_t *)base;

    fifo->data = fifo->queue[ fifo->base.read_index ];
    fifo->base.read_index++;
    fifo->base.fill--;
    fifo->base.read_index = ( fifo->base.read_index & ( fifo->base.max - 1U ) );
}

void Flush( fifo_base_t * const base )
{
    assert(base != NULL );
}

void test_FIFO_Init(void)
{
    test_fifo_t fifo;
    FIFO_Init( (fifo_base_t *)&fifo, FIFO_LEN );
 
    TEST_ASSERT_EQUAL( FIFO_LEN, fifo.base.max );
    TEST_ASSERT_EQUAL( 0U, fifo.base.fill );
    TEST_ASSERT_EQUAL( 0U, fifo.base.read_index );
    TEST_ASSERT_EQUAL( 0U, fifo.base.write_index );
}

void test_FIFO_Enqueue(void)
{
    test_fifo_t fifo;
    Init(&fifo);

    ENQUEUE(fifo, 0x12345678);

    TEST_ASSERT_EQUAL( 32U, fifo.base.max );
    TEST_ASSERT_EQUAL( 1U, fifo.base.fill );
    TEST_ASSERT_EQUAL( 0U, fifo.base.read_index );
    TEST_ASSERT_EQUAL( 1U, fifo.base.write_index );
    TEST_ASSERT_EQUAL( 0x12345678, fifo.queue[0U]);
}

void test_FIFO_Dequeue(void)
{
    test_fifo_t fifo;
    Init(&fifo);

    ENQUEUE(fifo, 0x12345678);
    
    TEST_ASSERT_EQUAL( 32U, fifo.base.max );
    TEST_ASSERT_EQUAL( 1U, fifo.base.fill );
    TEST_ASSERT_EQUAL( 0U, fifo.base.read_index );
    TEST_ASSERT_EQUAL( 1U, fifo.base.write_index );
    TEST_ASSERT_EQUAL( 0x12345678, fifo.queue[0U]);
    
    uint32_t value = DEQUEUE(fifo);

    TEST_ASSERT_EQUAL( 32U, fifo.base.max );
    TEST_ASSERT_EQUAL( 0U, fifo.base.fill );
    TEST_ASSERT_EQUAL( 1U, fifo.base.read_index );
    TEST_ASSERT_EQUAL( 1U, fifo.base.write_index );
    TEST_ASSERT_EQUAL( 0x12345678, value );
}

/*
void test_FIFO_EnqueueMany(void)
{
    test_fifo_t fifo;
    FIFO_InitUInt32(&fifo);

    for( uint32_t idx = 0; idx < 32; idx++ )
    {
        FIFO_ENQUInt32(&fifo, 0x12345678);
        TEST_ASSERT_EQUAL( 32U, fifo.base.max );
        TEST_ASSERT_EQUAL( idx + 1U, fifo.base.fill );
        TEST_ASSERT_EQUAL( 0U, fifo.base.read_index );
        TEST_ASSERT_EQUAL( (idx + 1U)%32, fifo.base.write_index );
        TEST_ASSERT_EQUAL( 0x12345678, fifo.queue[idx]);
    }
}

void test_FIFO_DequeueMany(void)
{
    test_fifo_t fifo;
    FIFO_InitUInt32(&fifo);

    for( uint32_t idx = 0; idx < 32; idx++ )
    {
        FIFO_ENQUInt32(&fifo, 0x12345678);
    }

    TEST_ASSERT_EQUAL( 32U, fifo.base.fill );

    uint32_t currentFill = fifo.base.fill;
    for( uint32_t idx = 0; idx < 32; idx++ )
    {
        uint32_t value = FIFO_DEQUInt32(&fifo);
        currentFill--;
        TEST_ASSERT_EQUAL( 32U, fifo.base.max );
        TEST_ASSERT_EQUAL( currentFill, fifo.base.fill );
        TEST_ASSERT_EQUAL( (idx + 1U)%32, fifo.base.read_index );
        TEST_ASSERT_EQUAL( 0U, fifo.base.write_index );
        TEST_ASSERT_EQUAL( 0x12345678, value);

    }
}

void test_FIFO_NotEmpty(void)
{
    test_fifo_t fifo;
    FIFO_InitUInt32(&fifo);

    TEST_ASSERT_FALSE( FIFO_NEUInt32(&fifo));
    FIFO_ENQUInt32(&fifo,0xFFFFFFFF);
    TEST_ASSERT_TRUE( FIFO_NEUInt32(&fifo));
}

void test_FIFO_IsFull(void)
{
    test_fifo_t fifo;
    FIFO_InitUInt32(&fifo);

    for( uint32_t idx = 0; idx < 32; idx++ )
    {
        TEST_ASSERT_FALSE(FIFO_ISFULLUInt32(&fifo));
        FIFO_ENQUInt32(&fifo, 0x12345678);
    }
    TEST_ASSERT_TRUE(FIFO_ISFULLUInt32(&fifo));
}
*/

extern void FIFOTestSuite(void)
{
    RUN_TEST(test_FIFO_Init);
    RUN_TEST(test_FIFO_Enqueue);
    RUN_TEST(test_FIFO_Dequeue);
    /*
    RUN_TEST(test_FIFO_EnqueueMany);
    RUN_TEST(test_FIFO_DequeueMany);
    RUN_TEST(test_FIFO_NotEmpty);
    RUN_TEST(test_FIFO_IsFull);
    */
}
