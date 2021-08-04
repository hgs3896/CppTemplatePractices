#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

template <typename KeyType>
class LRUCache
{
    using list_t = list<KeyType>;
    using list_iterator = typename list_t::iterator;

    // store keys of cache
    list_t dq;

    // store references of key in cache
    unordered_map<KeyType, list_iterator> ma;
    size_t csize; // maximum capacity of cache
    size_t fault_cnt;

public:
    // Declare the size
    explicit LRUCache(size_t n)
        : dq(), ma(), csize(n), fault_cnt()
    {
    }

    // Refers key x with in the LRU cache
    void refer(const KeyType &x)
    {
        // not present in cache
        if (ma.find(x) == ma.end()) // lookup: O(1)
        {
            // cache is full
            if (dq.size() == csize)
            {
                // count the page fault
                ++this->fault_cnt;

                // delete least recently used element
                KeyType last = dq.back();

                // Pops the last elmeent
                dq.pop_back(); // deletion: O(1)

                // Erase the last
                ma.erase(last); // deletion: O(1)
            }
        }
        else
        {
            // present in cache
            dq.erase(ma[x]); // deletion: O(1)
        }

        // update reference
        dq.push_front(x);   // insertion: O(1)
        ma[x] = dq.begin(); // insert or update: O(1)
    }

    // Function to display contents of cache
    void display() const
    {
        // Iterate in the deque and print
        // all the elements in it

        // Print one item
        const auto print_item = [](const auto &item)
        { std::cout << "[ " << item << " ]"; };

        std::cout << "# of Page Faults:\t" << this->fault_cnt << endl;
        print_item(*dq.begin());
        for (auto it = std::next(dq.begin()); it != dq.end(); it++)
        {
            cout << " - ";
            print_item(*it);
        }
        cout << endl;
    }
};