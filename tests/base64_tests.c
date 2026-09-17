#include "unity.h"
#include "base64_tests.h"
#include "base64.h"
#include <string.h>

void test_BASE64_EncodeTest0(void)
{
    char * test_vector = "foo";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Encode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 3u);
    TEST_ASSERT_EQUAL(out_len, 4u);
    TEST_ASSERT_EQUAL_STRING("Zm9v", output);
}

void test_BASE64_EncodeTest1(void)
{
    char * test_vector = "foobar";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Encode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 6u);
    TEST_ASSERT_EQUAL(out_len, 8u);
    TEST_ASSERT_EQUAL_STRING("Zm9vYmFy", output);
}

void test_BASE64_EncodeTest2(void)
{
    char * test_vector = "fo";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Encode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 2u);
    TEST_ASSERT_EQUAL(out_len, 4u);
    TEST_ASSERT_EQUAL_STRING("Zm8=", output);
}

void test_BASE64_EncodeTest3(void)
{
    char * test_vector = "f";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Encode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 1u);
    TEST_ASSERT_EQUAL(out_len, 4u);
    TEST_ASSERT_EQUAL_STRING("Zg==", output);
}

void test_BASE64_EncodeTest4(void)
{
    char * test_vector = "";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Encode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 0u);
    TEST_ASSERT_EQUAL(out_len, 0);
    TEST_ASSERT_EQUAL_STRING("", output);
}

void test_BASE64_EncodeTest5(void)
{
    char * test_vector = "foob";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Encode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 4u);
    TEST_ASSERT_EQUAL(out_len, 8u);
    TEST_ASSERT_EQUAL_STRING("Zm9vYg==", output);
}

void test_BASE64_EncodeTest6(void)
{
    char * test_vector = "fooba";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Encode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 5u);
    TEST_ASSERT_EQUAL(out_len, 8u);
    TEST_ASSERT_EQUAL_STRING("Zm9vYmE=", output);
}

void test_BASE64_DecodeTest0(void)
{
    char * test_vector = "Zm9v";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Decode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 4u);
    TEST_ASSERT_EQUAL(out_len, 3u);
    TEST_ASSERT_EQUAL_STRING("foo", output);
}

void test_BASE64_DecodeTest1(void)
{
    char * test_vector = "Zm9vYmFy";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Decode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 8u);
    TEST_ASSERT_EQUAL(out_len, 6u);
    TEST_ASSERT_EQUAL_STRING("foobar", output);
}

void test_BASE64_DecodeTest2(void)
{
    char * test_vector = "Zm8=";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Decode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 4u);
    TEST_ASSERT_EQUAL(out_len, 2u);
    TEST_ASSERT_EQUAL_STRING("fo", output);
}

void test_BASE64_DecodeTest3(void)
{
    char * test_vector = "Zg==";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Decode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 4u);
    TEST_ASSERT_EQUAL(out_len, 1u);
    TEST_ASSERT_EQUAL_STRING("f", output);
}

void test_BASE64_DecodeTest4(void)
{
    char * test_vector = "";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Decode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 0u);
    TEST_ASSERT_EQUAL(out_len, 0u);
    TEST_ASSERT_EQUAL_STRING("", output);
}

void test_BASE64_DecodeTest5(void)
{
    char * test_vector = "Zm9vYg==";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Decode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 8u);
    TEST_ASSERT_EQUAL(out_len, 4u);
    TEST_ASSERT_EQUAL_STRING("foob", output);
}

void test_BASE64_DecodeTest6(void)
{
    char * test_vector = "Zm9vYmE=";
    char output[32] = {0};
    uint32_t len = strlen(test_vector);
    uint32_t out_len = BASE64_Decode((uint8_t*)test_vector,len,(uint8_t*)output);

    TEST_ASSERT_EQUAL(len, 8u);
    TEST_ASSERT_EQUAL(out_len, 5u);
    TEST_ASSERT_EQUAL_STRING("fooba", output);
}

extern void BASE64TestSuite(void)
{
    RUN_TEST(test_BASE64_EncodeTest0);
    RUN_TEST(test_BASE64_EncodeTest1);
    RUN_TEST(test_BASE64_EncodeTest2);
    RUN_TEST(test_BASE64_EncodeTest3);
    RUN_TEST(test_BASE64_EncodeTest4);
    RUN_TEST(test_BASE64_EncodeTest5);
    RUN_TEST(test_BASE64_EncodeTest6);
    RUN_TEST(test_BASE64_DecodeTest0);
    RUN_TEST(test_BASE64_DecodeTest1);
    RUN_TEST(test_BASE64_DecodeTest2);
    RUN_TEST(test_BASE64_DecodeTest3);
    RUN_TEST(test_BASE64_DecodeTest4);
    RUN_TEST(test_BASE64_DecodeTest5);
    RUN_TEST(test_BASE64_DecodeTest6);
}
