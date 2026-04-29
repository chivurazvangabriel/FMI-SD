#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct MyDeque {
    vector<T*> blocks;
    int blockSize = 512;
    int startBlock, startIndex;
    int endBlock, endIndex;
    int totalElements;

    MyDeque() {
        startBlock = endBlock = 0;
        startIndex = endIndex = blockSize / 2;
        blocks.push_back(new T[blockSize]);
        totalElements = 0;
    }

    void push_back(T val) {
        blocks[endBlock][endIndex] = val;
        endIndex++;
        if (endIndex == blockSize) {
            endIndex = 0;
            endBlock++;
            blocks.push_back(new T[blockSize]);
        }
        totalElements++;
    }

    void push_front(T val) {
        if (startIndex == 0) {
            startIndex = blockSize - 1;
            startBlock++;
        } else {
            startIndex--;
        }
        blocks[0][startIndex] = val;
        totalElements++;
    }

    T& operator[](int index) {
        int actualIndex = startIndex + index;
        int blockIdx = actualIndex / blockSize;
        int innerIdx = actualIndex % blockSize;
        return blocks[blockIdx][innerIdx];
    }
};