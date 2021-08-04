#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

template <typename KeyType>
class LFUCache
{
    struct Block
    {
        KeyType key;
        size_t cnt;
        bool operator<(const Block &rhs) const
        {
            return this->cnt < rhs.cnt;
        }
    };
    using pq_t = multimap<size_t, Block>;
    using pq_iterator = typename pq_t::iterator;
    // store keys of cache
    pq_t pq;

    // store references of key in cache
    unordered_map<KeyType, pq_iterator> ma;
    size_t csize; // maximum capacity of cache
    size_t fault_cnt;

public:
    // Declare the size
    explicit LFUCache(size_t n)
        : pq(), ma(), csize(n), fault_cnt()
    {
    }

    // Refers key x with in the LRU cache
    void refer(const KeyType &x)
    {
        // not present in cache
        if (ma.find(x) == ma.end()) // lookup: O(1)
        {
            // cache is full
            if (pq.size() == csize)
            {
                // count the page fault
                ++this->fault_cnt;

                pq_iterator block_it = pq.begin();

                // Erase the last
                ma.erase(block_it->second.key); // deletion: O(1)

                // Pops the last elmeent
                pq.erase(block_it); // deletion: O(lg(n))
            }

            // update reference
            auto it = pq.emplace(1, Block{x, 1}); // insertion: O(lg(n))
            ma[x] = it;                           // insert or update: O(1)
        }
        else
        {
            // present in cache
            const Block &blk = ma[x]->second;
            // update reference
            auto it = pq.emplace(blk.cnt + 1, Block{blk.key, blk.cnt + 1}); // insertion: O(lg(n))
            pq.erase(ma[x]);                                                // deletion: O(lg(n))
            ma[x] = it;                                                     // insert or update: O(1)
        }
    }

    // Function to display contents of cache
    void display() const
    {
        // Iterate in the deque and print
        // all the elements in it

        // Print one item
        const auto print_item = [](const auto &item)
        { std::cout << "[ " << item.second.key << "(" << item.second.cnt << ") ]"; };

        std::cout << "# of Page Faults:\t" << this->fault_cnt << endl;

        print_item(*pq.begin());
        for (auto it = std::next(pq.begin()); it != pq.end(); it++)
        {
            cout << " - ";
            print_item(*it);
        }
        cout << endl;
    }
};