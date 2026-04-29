#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Node {
    int val;
    int aggregate;
};

void push(stack<Node>& s, int val, int (*f)(int, int), int identity) {
    int current_agg = s.empty() ? identity : s.top().aggregate;
    s.push({val, f(current_agg, val)});
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    auto f = [](int x, int y) { return x | y; };
    int identity = 0;

    stack<Node> s1, s2;

    for (int i = 0; i < n; i++) {
        push(s1, a[i], f, identity);

        if (i >= k - 1) {
            if (s2.empty()) {
                while (!s1.empty()) {
                    push(s2, s1.top().val, f, identity);
                    s1.pop();
                }
            }

            int res1 = s1.empty() ? identity : s1.top().aggregate;
            int res2 = s2.empty() ? identity : s2.top().aggregate;
            cout << f(res1, res2) << " ";

            if (!s2.empty()) s2.pop();
        }
    }

    return 0;
}