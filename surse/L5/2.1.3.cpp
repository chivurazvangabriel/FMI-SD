#include <iostream>
#include <vector>
#include <algorithm>

class BinaryTrie {
private:
    struct Node {
        Node* children[2];
        int last_index;
        Node() {
            children[0] = children[1] = nullptr;
            last_index = -1;
        }
    };

    Node* root;
    const int MAX_BITS = 30;

public:
    BinaryTrie() { root = new Node(); }

    void insert(int val, int index) {
        Node* curr = root;
        for (int i = MAX_BITS; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = new Node();
            }
            curr = curr->children[bit];
            curr->last_index = index;
        }
    }

    std::pair<int, int> getMaxXor(int val) {
        Node* curr = root;
        int xor_max = 0;
        for (int i = MAX_BITS; i >= 0; --i) {
            int bit = (val >> i) & 1;
            int desired_bit = 1 - bit;
            if (curr->children[desired_bit]) {
                xor_max |= (1 << i);
                curr = curr->children[desired_bit];
            } else {
                curr = curr->children[bit];
            }
        }
        return {xor_max, curr->last_index};
    }
};

int main() {
    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    BinaryTrie trie;
    trie.insert(0, -1);

    int current_xor = 0;
    int global_max_xor = -1;
    int best_l = 0, best_r = 0;

    for (int j = 0; j < n; ++j) {
        current_xor ^= a[j];
        auto result = trie.getMaxXor(current_xor);
        
        if (result.first > global_max_xor) {
            global_max_xor = result.first;
            best_l = result.second + 1;
            best_r = j;
        }
        trie.insert(current_xor, j);
    }

    std::cout << best_l << " " << best_r << std::endl;
    return 0;
}