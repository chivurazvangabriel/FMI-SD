#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class ChainingHash {
    vector<list<int>> table;
    int num_elements;
    float max_load_factor = 0.75;

    int hash_func(int x) {
        return abs(x) % table.size();
    }

    void resize() {
        int new_size = table.size() * 2;
        vector<list<int>> new_table(new_size);
        for (auto& bucket : table) {
            for (int val : bucket) {
                new_table[abs(val) % new_size].push_back(val);
            }
        }
        table = move(new_table);
    }

public:
    ChainingHash(int initial_size = 10) : table(initial_size), num_elements(0) {}

    void insert(int x) {
        if (exists(x)) return;
        if ((float)num_elements / table.size() > max_load_factor) {
            resize();
        }
        table[hash_func(x)].push_back(x);
        num_elements++;
    }

    void erase(int x) {
        int idx = hash_func(x);
        auto& bucket = table[idx];
        auto it = find(bucket.begin(), bucket.end(), x);
        if (it != bucket.end()) {
            bucket.erase(it);
            num_elements--;
        }
    }

    bool exists(int x) {
        int idx = hash_func(x);
        for (int val : table[idx]) {
            if (val == x) return true;
        }
        return false;
    }
};