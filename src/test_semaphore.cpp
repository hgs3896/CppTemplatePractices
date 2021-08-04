#include <vector>
#include <thread>
#include <iostream>
#include "semaphore.hpp"

int TEST_SEMAPHORE(){
    std::vector<std::thread> pool;
    Semaphore semaphore{4};
    for (size_t idx = 0; idx < (std::thread::hardware_concurrency() - 1) / 2 * 2; ++idx)
    {
        pool.emplace_back([idx, &semaphore]()
                          {
                              if (idx % 2)
                              {
                                  for (auto i = 0; i < 1000; ++i)
                                  {
                                      semaphore.get(idx);
                                  }
                              }
                              else
                              {
                                  for (auto i = 0; i < 1000; ++i)
                                  {
                                      semaphore.release(idx);
                                  }
                              }
                          });
    }
    for (auto &&thread : pool)
    {
        thread.join();
    }
    return 0;
}