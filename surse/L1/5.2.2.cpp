#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace std;

struct RandomSelector {
    vector<int> nums;
    unordered_map<int, int> posMap;

    void insert(int x) {
        if (posMap.find(x) != posMap.end()) return;
        posMap[x] = nums.size();
        nums.push_back(x);
    }

    void popRandom() {
        if (nums.empty()) return;
        int randomIndex = rand() % nums.size();
        int lastElement = nums.back();
        int elementToRemove = nums[randomIndex];

        nums[randomIndex] = lastElement;
        posMap[lastElement] = randomIndex;

        nums.pop_back();
        posMap.erase(elementToRemove);
        
        cout << "Popped: " << elementToRemove << endl;
    }
};