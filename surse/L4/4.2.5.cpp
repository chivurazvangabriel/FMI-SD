#include <iostream>
#include <queue>
#include <vector>

class MedianFinder {
private:
    std::priority_queue<int> max_heap; 
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap; 

public:
    void insert(int x) {
        if (max_heap.empty() || x <= max_heap.top()) {
            max_heap.push(x);
        } else {
            min_heap.push(x);
        }

        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    double getMedian() {
        if (max_heap.size() == min_heap.size()) {
            return (max_heap.top() + min_heap.top()) / 2.0;
        }
        return max_heap.top();
    }
};