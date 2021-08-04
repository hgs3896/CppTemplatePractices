#include "lfu_cache.hpp"

// Driver Code
int TEST_LFU_CACHE()
{    
    LFUCache<int> ca{4};
    ca.refer(1); // 1(1)
    ca.refer(2); // 1(1) - 2(1)
    ca.refer(3); // 1(1) - 2(1) - 3(1)
    ca.refer(4); // 1(1) - 2(1) - 3(1) - 4(1)
    ca.refer(1); // 2(1) - 3(1) - 4(1) - 1(2)
    ca.refer(2); // 3(1) - 4(1) - 1(2) - 2(2)
    ca.refer(5); // 4(1) - 5(1) - 1(2) - 2(2) (- 3; evicted)
    ca.refer(1); // 4(1) - 5(1) - 2(2) - 1(3)
    ca.refer(2); // 4(1) - 5(1) - 1(3) - 2(3)
    ca.refer(3); // 5(1) - 3(1) - 1(3) - 2(3) (- 4; evicted)
    ca.refer(4); // 3(1) - 4(1) - 1(3) - 2(3) (- 5; evicted)
    ca.refer(5); // 4(1) - 5(1) - 1(3) - 2(3) (- 3; evicted)
    ca.display();

    return 0;
}