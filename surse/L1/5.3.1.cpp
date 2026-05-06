#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

struct MyList {
    Node* head = nullptr;

    void insertFront(int x) {
        Node* newNode = new Node(x);
        newNode->next = head;
        head = newNode;
    }

    void insertEnd(int x) {
        if (!head) {
            head = new Node(x);
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = new Node(x);
    }

    void eraseFront() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    Node* findByValue(int x) {
        Node* temp = head;
        while (temp) {
            if (temp->val == x) return temp;
            temp = temp->next;
        }
        return nullptr;
    }
};