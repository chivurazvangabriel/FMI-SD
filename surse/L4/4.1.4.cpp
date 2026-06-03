#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <climits>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
private:
    void serializeHelper(TreeNode* root, std::stringstream& ss) {
        if (!root) return;
        ss << root->val << " ";
        serializeHelper(root->left, ss);
        serializeHelper(root->right, ss);
    }

    TreeNode* deserializeHelper(const std::vector<int>& data, int& idx, int min_val, int max_val) {
        if (idx >= data.size()) return nullptr;
        int val = data[idx];
        if (val < min_val || val > max_val) return nullptr;

        idx++;
        TreeNode* root = new TreeNode(val);
        root->left = deserializeHelper(data, idx, min_val, val);
        root->right = deserializeHelper(data, idx, val, max_val);
        return root;
    }

public:
    std::string serialize(TreeNode* root) {
        std::stringstream ss;
        serializeHelper(root, ss);
        return ss.str();
    }

    TreeNode* deserialize(std::string data) {
        if (data.empty()) return nullptr;
        std::stringstream ss(data);
        std::vector<int> vals;
        int val;
        while (ss >> val) {
            vals.push_back(val);
        }
        int idx = 0;
        return deserializeHelper(vals, idx, INT_MIN, INT_MAX);
    }
};