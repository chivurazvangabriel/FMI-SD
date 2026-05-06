#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
};

void detectCycle(Node* head) {
    if (!head) return;
    Node *slow = head, *fast = head;
    bool hasCycle = false;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }

    if (hasCycle) {
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        Node* startNode = slow;
        int length = 0;
        do {
            fast = fast->next;
            length++;
        } while (fast != slow);
        
        cout << "Cycle start value: " << startNode->val << endl;
        cout << "Cycle length: " << length << endl;
    }
}