#include "lru_cache.hpp"

// Driver Code
int TEST_LRU_CACHE()
{
    LRUCache<int> ca {4};
    ca.refer(1); // 1
    ca.refer(2); // 2 - 1
    ca.refer(3); // 3 - 2 - 1
    ca.refer(4); // 4 - 3 - 2 - 1
    ca.refer(1); // 1 - 4 - 3 - 2
    ca.refer(2); // 2 - 1 - 4 - 3
    ca.refer(5); // 5 - 2 - 1 - 4 (- 3; evicted)
    ca.refer(1); // 1 - 5 - 2 - 4
    ca.refer(2); // 2 - 1 - 5 - 4
    ca.refer(3); // 3 - 2 - 1 - 5 (- 4; evicted)
    ca.refer(4); // 4 - 3 - 2 - 1 (- 5; evicted)
    ca.refer(5); // 5 - 4 - 3 - 2 (- 1; evicted)
    ca.display();

    return 0;
}