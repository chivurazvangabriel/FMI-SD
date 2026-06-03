#include <iostream>
#include <vector>
#include <queue>

long long getMinCost(const std::vector<int>& sticks) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    
    for (int length : sticks) {
        pq.push(length);
    }
    
    long long total_cost = 0;
    
    while (pq.size() > 1) {
        int first = pq.top(); pq.pop();
        int second = pq.top(); pq.pop();
        
        int current_cost = first + second;
        total_cost += current_cost;
        
        pq.push(current_cost);
    }
    
    return total_cost;
}