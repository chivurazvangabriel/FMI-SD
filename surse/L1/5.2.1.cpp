#include <iostream>

using namespace std;

struct MyVector {
    int* data;
    int capacity;
    int size;

    void init() {
        capacity = 1;
        size = 0;
        data = new int[capacity];
    }

    void push_back(int x) {
        if (size == capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < size; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
        }
        data[size++] = x;
    }

    void pop_back() {
        if (size > 0) size--;
    }

    int get_size() {
        return size;
    }
};