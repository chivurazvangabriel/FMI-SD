#include <unordered_map>
#include <list>

using namespace std;

struct Node {
    int key, value, freq;
};

class LFUCache {
    int capacity, minFreq;
    unordered_map<int, list<Node>::iterator> keyMap;
    unordered_map<int, list<Node>> freqMap;

    void updateFreq(int key) {
        auto it = keyMap[key];
        Node node = *it;
        freqMap[node.freq].erase(it);
        if (freqMap[node.freq].empty() && node.freq == minFreq) minFreq++;
        node.freq++;
        freqMap[node.freq].push_front(node);
        keyMap[key] = freqMap[node.freq].begin();
    }

public:
    LFUCache(int k) : capacity(k), minFreq(0) {}

    int get(int key) {
        if (keyMap.find(key) == keyMap.end()) return -1;
        updateFreq(key);
        return keyMap[key]->value;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;
        if (get(key) != -1) {
            keyMap[key]->value = value;
            return;
        }
        if (keyMap.size() >= capacity) {
            int kToEvict = freqMap[minFreq].back().key;
            keyMap.erase(kToEvict);
            freqMap[minFreq].pop_back();
        }
        minFreq = 1;
        freqMap[1].push_front({key, value, 1});
        keyMap[key] = freqMap[1].begin();
    }
};