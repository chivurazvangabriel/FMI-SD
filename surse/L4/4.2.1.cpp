#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

class MinHeap {
private:
    std::vector<int> heap;

    void heapifyUp(int idx) {
        while (idx > 0) {
            int p = (idx - 1) / 2;
            if (heap[idx] < heap[p]) {
                std::swap(heap[idx], heap[p]);
                idx = p;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int idx) {
        int n = heap.size();
        while (2 * idx + 1 < n) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = left;

            if (right < n && heap[right] < heap[left]) {
                smallest = right;
            }

            if (heap[smallest] < heap[idx]) {
                std::swap(heap[idx], heap[smallest]);
                idx = smallest;
            } else {
                break;
            }
        }
    }

public:
    void insert(int x) {
        heap.push_back(x);
        heapifyUp(heap.size() - 1);
    }

    int top() {
        if (heap.empty()) throw std::runtime_error("Heap is empty");
        return heap[0];
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }
};