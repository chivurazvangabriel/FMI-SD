#include <iostream>
#include <map>
#include <cmath>

struct Node {
    int value;
    Node* left;
    Node* right;
};

class RSBT {
private:
    std::map<int, long long> solveNode(Node* node) {
        if (!node) {
            return {{1, 1}}; 
        }

        auto left_ways = solveNode(node->left);
        auto right_ways = solveNode(node->right);
        std::map<int, long long> current_ways;

        for (auto const& [h_l, count_l] : left_ways) {
            for (auto const& [h_r, count_r] : right_ways) {
                if (std::abs(h_l - h_r) <= 1) {
                    long long ways_combinations = count_l * count_r;
                    
                    int h_max = std::max(h_l, h_r);
                    current_ways[h_max] += ways_combinations; 
                    current_ways[h_max + 1] += ways_combinations; 
                }
            }
        }
        return current_ways;
    }

public:
    long long countColorings(Node* root) {
        auto total_ways = solveNode(root);
        long long sum = 0;
        for (auto const& [h, count] : total_ways) {
            sum += count;
        }
        return sum;
    }
};