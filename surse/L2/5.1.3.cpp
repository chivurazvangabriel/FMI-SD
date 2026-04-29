#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool knows(int a, int b);

int findCelebrity(int n) {
    stack<int> s;
    for (int i = 0; i < n; i++) s.push(i);

    while (s.size() > 1) {
        int a = s.top(); s.pop();
        int b = s.top(); s.pop();

        if (knows(a, b)) s.push(b);
        else s.push(a);
    }

    int candidate = s.top();
    for (int i = 0; i < n; i++) {
        if (i != candidate) {
            if (knows(candidate, i) || !knows(i, candidate)) return -1;
        }
    }
    return candidate;
}