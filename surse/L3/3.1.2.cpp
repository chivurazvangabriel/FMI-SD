#include <iostream>
#include <vector>

using namespace std;

class OpenAddressingHash {
    struct Entry {
        int key;
        bool occupied = false;
        bool deleted = false;
    };

    vector<Entry> table;
    int num_elements;

    int hash_func(int x, int i) {
        return (abs(x) + i) % table.size();
    }

public:
    OpenAddressingHash(int size = 11) : table(size), num_elements(0) {}

    void insert(int x) {
        if (num_elements > table.size() * 0.5) { }
        for (int i = 0; i < table.size(); i++) {
            int idx = hash_func(x, i);
            if (!table[idx].occupied) {
                table[idx] = {x, true, false};
                num_elements++;
                return;
            }
            if (table[idx].key == x && !table[idx].deleted) return;
        }
    }

    bool exists(int x) {
        for (int i = 0; i < table.size(); i++) {
            int idx = hash_func(x, i);
            if (!table[idx].occupied) return false;
            if (table[idx].key == x && !table[idx].deleted) return true;
        }
        return false;
    }

    void erase(int x) {
        for (int i = 0; i < table.size(); i++) {
            int idx = hash_func(x, i);
            if (!table[idx].occupied) return;
            if (table[idx].key == x && !table[idx].deleted) {
                table[idx].deleted = true;
                num_elements--;
                return;
            }
        }
    }
};