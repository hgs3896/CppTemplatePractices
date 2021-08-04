#include <iostream>
#define REGISTER_TEST(TEST_NAME) extern int TEST_ ## TEST_NAME();
#define TEST(TEST_NAME) { \
    std::cout << "Test [" << #TEST_NAME << "] is running..." << std::endl; \
    /* Run the test. */ \
    TEST_##TEST_NAME(); \
    std::cout << "Test [" << #TEST_NAME << "] finished." << std::endl; \
}

REGISTER_TEST(SEMAPHORE)
REGISTER_TEST(LRU_CACHE)
REGISTER_TEST(LFU_CACHE)

int main()
{
    TEST(SEMAPHORE);
    TEST(LRU_CACHE);
    TEST(LFU_CACHE);
    return 0;   
}