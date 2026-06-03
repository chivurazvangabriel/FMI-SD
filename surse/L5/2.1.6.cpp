#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class DynamicXorTrie {
private:
    struct Node {
        Node* children[2];
        int count;
        Node() {
            children[0] = children[1] = nullptr;
            count = 0;
        }
    };

    Node* root;
    const int MAX_BITS = 30;

    void change(int val, int delta) {
        Node* curr = root;
        for (int i = MAX_BITS; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = new Node();
            }
            curr = curr->children[bit];
            curr->count += delta;
        }
    }

public:
    DynamicXorTrie() { root = new Node(); }

    void insert(int val) { change(val, 1); }
    void erase(int val) { change(val, -1); }

    int getMaxXor(int val) {
        if (root->count == 0) return 0;
        Node* curr = root;
        int xor_max = 0;
        for (int i = MAX_BITS; i >= 0; --i) {
            int bit = (val >> i) & 1;
            int desired_bit = 1 - bit;
            if (curr->children[desired_bit] && curr->children[desired_bit]->count > 0) {
                xor_max |= (1 << i);
                curr = curr->children[desired_bit];
            } else {
                curr = curr->children[bit];
            }
        }
        return xor_max;
    }
};

struct Query {
    int type;
    int l, r;
    int val;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> a(n);
    std::vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        pref[i + 1] = pref[i] ^ a[i];
    }

    std::vector<int> disable_order(n);
    std::vector<bool> initially_enabled(n, true);
    for (int i = 0; i < n; ++i) {
        std::cin >> disable_order[i];
        disable_order[i]--; 
    }

    std::vector<int> rev_order = disable_order;
    std::reverse(rev_order.begin(), rev_order.end());

    std::set<std::pair<int, int>> segments;
    std::multiset<int> max_segment_xors;
    DynamicXorTrie trie;

    auto get_best_xor_in_segment = [&](int l, int r) {
        DynamicXorTrie local_trie;
        local_trie.insert(pref[l]);
        int best = 0;
        for (int i = l; i <= r; ++i) {
            best = std::max(best, local_trie.getMaxXor(pref[i + 1]));
            local_trie.insert(pref[i + 1]);
        }
        return best;
    };

    std::vector<int> answers;
    std::vector<bool> active(n, false);

    for (int idx : rev_order) {
        int l = idx, r = idx;
        active[idx] = true;

        auto it = segments.lower_bound({idx, 0});
        
        if (it != segments.end() && it->first == idx + 1) {
            r = it->second;
            int old_xor = get_best_xor_in_segment(it->first, it->second);
            max_segment_xors.erase(max_segment_xors.find(old_xor));
            segments.erase(it);
        }

        it = segments.lower_bound({idx, 0});
        if (it != segments.begin()) {
            --it;
            if (it->second == idx - 1) {
                l = it->first;
                int old_xor = get_best_xor_in_segment(it->first, it->second);
                max_segment_xors.erase(max_segment_xors.find(old_xor));
                segments.erase(it);
            }
        }

        segments.insert({l, r});
        int new_xor = get_best_xor_in_segment(l, r);
        max_segment_xors.insert(new_xor);

        answers.push_back(max_segment_xors.empty() ? 0 : *max_segment_xors.rbegin());
    }

    std::reverse(answers.begin(), answers.end());
    for (int ans : answers) {
        std::cout << ans << "\n";
    }

    return 0;
}