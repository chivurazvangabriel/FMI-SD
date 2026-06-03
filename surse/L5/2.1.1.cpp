#include <iostream>
#include <string>
#include <vector>

class Trie {
private:
    struct Node {
        Node* children[26];
        int word_count;
        int prefix_count;

        Node() {
            for (int i = 0; i < 26; ++i) {
                children[i] = nullptr;
            }
            word_count = 0;
            prefix_count = 0;
        }
    };

    Node* root;

    bool eraseHelper(Node* curr, const std::string& s, int idx) {
        if (!curr) return false;

        curr->prefix_count--;

        if (idx == s.length()) {
            curr->word_count--;
            if (curr->word_count == 0 && curr->prefix_count == 0) {
                delete curr;
                return true;
            }
            return false;
        }

        int char_idx = s[idx] - 'a';
        if (eraseHelper(curr->children[char_idx], s, idx + 1)) {
            curr->children[char_idx] = nullptr;
        }

        if (curr != root && curr->prefix_count == 0) {
            delete curr;
            return true;
        }

        return false;
    }

    void destroy(Node* curr) {
        if (!curr) return;
        for (int i = 0; i < 26; ++i) {
            if (curr->children[i]) {
                destroy(curr->children[i]);
            }
        }
        delete curr;
    }

public:
    Trie() {
        root = new Node();
    }

    ~Trie() {
        destroy(root);
    }

    void insert(const std::string& s) {
        Node* curr = root;
        curr->prefix_count++;
        for (char ch : s) {
            int idx = ch - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = new Node();
            }
            curr = curr->children[idx];
            curr->prefix_count++;
        }
        curr->word_count++;
    }

    void erase(const std::string& s) {
        if (count(s) == 0) return;
        eraseHelper(root, s, 0);
    }

    int count(const std::string& s) {
        Node* curr = root;
        for (char ch : s) {
            int idx = ch - 'a';
            if (!curr->children[idx]) return 0;
            curr = curr->children[idx];
        }
        return curr->word_count;
    }

    int longest_prefix(const std::string& s) {
        Node* curr = root;
        int length = 0;
        for (char ch : s) {
            int idx = ch - 'a';
            if (!curr->children[idx] || curr->children[idx]->prefix_count == 0) {
                break;
            }
            curr = curr->children[idx];
            length++;
        }
        return length;
    }
};