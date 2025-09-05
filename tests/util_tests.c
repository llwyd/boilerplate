#include "util.h"
#include "tests_bp.h"
#include "unity.h"

static void * Populate(void * buffer, uint8_t ch, uint16_t len)
{
    return TESTBP_memset(buffer,ch,len);
}

void test_Util_memset8(void)
{
    uint8_t a[8];
    uint8_t ref[8];
    uint8_t * a_ptr = NULL;
    uint8_t * ref_ptr = NULL;

    TEST_ASSERT_NOT_EQUAL(a, a_ptr);
    TEST_ASSERT_NOT_EQUAL(ref, ref_ptr);
    a_ptr = (uint8_t *)memset(a, 0x00, 8 * sizeof(uint8_t));
    ref_ptr = (uint8_t *)Populate(ref, 0x00, 8 * sizeof(uint8_t));
   
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint8_t), 8);
    
    a_ptr = (uint8_t *)memset(a, 0x55, 8 * sizeof(uint8_t));
    ref_ptr = (uint8_t *)Populate(ref, 0x55, 8 * sizeof(uint8_t));
    
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint8_t), 8);
    
    a_ptr = (uint8_t *)memset(a, 0xaa, 8 * sizeof(uint8_t));
    ref_ptr = (uint8_t *)Populate(ref, 0xaa, 8 * sizeof(uint8_t));
    
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint8_t), 8);
}

void test_Util_memset16(void)
{
    uint16_t a[8];
    uint16_t ref[8];
    uint16_t * a_ptr = NULL;
    uint16_t * ref_ptr = NULL;

    TEST_ASSERT_NOT_EQUAL(a, a_ptr);
    TEST_ASSERT_NOT_EQUAL(ref, ref_ptr);
    a_ptr = (uint16_t *)memset(a, 0x00, 8 * sizeof(uint16_t));
    ref_ptr = (uint16_t *)Populate(ref, 0x00, 8 * sizeof(uint16_t));
   
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint16_t), 8);
    
    a_ptr = (uint16_t *)memset(a, 0x55, 8 * sizeof(uint16_t));
    ref_ptr = (uint16_t *)Populate(ref, 0x55, 8 * sizeof(uint16_t));
    
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint16_t), 8);
    
    a_ptr = (uint16_t *)memset(a, 0xaa, 8 * sizeof(uint16_t));
    ref_ptr = (uint16_t *)Populate(ref, 0xaa, 8 * sizeof(uint16_t));
    
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint16_t), 8);
}

void test_Util_memset32(void)
{
    uint32_t a[8];
    uint32_t ref[8];
    uint32_t * a_ptr = NULL;
    uint32_t * ref_ptr = NULL;

    TEST_ASSERT_NOT_EQUAL(a, a_ptr);
    TEST_ASSERT_NOT_EQUAL(ref, ref_ptr);
    a_ptr = (uint32_t *)memset(a, 0x00, 8 * sizeof(uint32_t));
    ref_ptr = (uint32_t *)Populate(ref, 0x00, 8 * sizeof(uint32_t));
   
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint32_t), 8);
    
    a_ptr = (uint32_t *)memset(a, 0x55, 8 * sizeof(uint32_t));
    ref_ptr = (uint32_t *)Populate(ref, 0x55, 8 * sizeof(uint32_t));
    
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint32_t), 8);
    
    a_ptr = (uint32_t *)memset(a, 0xaa, 8 * sizeof(uint32_t));
    ref_ptr = (uint32_t *)Populate(ref, 0xaa, 8 * sizeof(uint32_t));
    
    TEST_ASSERT_EQUAL(a, a_ptr);
    TEST_ASSERT_EQUAL(ref, ref_ptr);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(a, ref, sizeof(uint32_t), 8);
}

extern void UtilTestSuite(void)
{
    RUN_TEST(test_Util_memset8);
    RUN_TEST(test_Util_memset16);
    RUN_TEST(test_Util_memset32);
}

