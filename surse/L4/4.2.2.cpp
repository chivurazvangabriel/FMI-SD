#include <iostream>
#include <vector>
#include <queue>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        std::priority_queue<ListNode*, std::vector<ListNode*>, Compare> pq;
        
        for (auto list : lists) {
            if (list) pq.push(list);
        }
        
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (!pq.empty()) {
            ListNode* curr = pq.top();
            pq.pop();
            
            tail->next = curr;
            tail = tail->next;
            
            if (curr->next) {
                pq.push(curr->next);
            }
        }
        
        return dummy.next;
    }
};