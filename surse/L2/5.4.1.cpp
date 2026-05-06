#include <atomic>
#include <vector>

template <typename T>
class SPSCQueue {
    struct Node {
        T data;
        std::atomic<bool> ready{false};
    };

    std::vector<Node> buffer;
    std::atomic<size_t> head{0};
    std::atomic<size_t> tail{0};
    size_t capacity;

public:
    SPSCQueue(size_t cap) : capacity(cap) {
        buffer.resize(cap);
    }

    bool push(const T& val) {
        size_t currentTail = tail.load(std::memory_order_relaxed);
        size_t nextTail = (currentTail + 1) % capacity;

        if (nextTail == head.load(std::memory_order_acquire)) return false;

        buffer[currentTail].data = val;
        buffer[currentTail].ready.store(true, std::memory_order_release);
        tail.store(nextTail, std::memory_order_release);
        return true;
    }

    bool pop(T& result) {
        size_t currentHead = head.load(std::memory_order_relaxed);
        if (currentHead == tail.load(std::memory_order_acquire)) return false;

        result = buffer[currentHead].data;
        head.store((currentHead + 1) % capacity, std::memory_order_release);
        return true;
    }
};