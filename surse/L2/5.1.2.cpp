#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

long long getMaxArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> s;
    long long maxArea = 0;
    int i = 0;

    while (i < n) {
        if (s.empty() || heights[s.top()] <= heights[i]) {
            s.push(i++);
        } else {
            int tp = s.top();
            s.pop();
            long long area = (long long)heights[tp] * (s.empty() ? i : i - s.top() - 1);
            maxArea = max(maxArea, area);
        }
    }

    while (!s.empty()) {
        int tp = s.top();
        s.pop();
        long long area = (long long)heights[tp] * (s.empty() ? i : i - s.top() - 1);
        maxArea = max(maxArea, area);
    }

    return maxArea;
}

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; i++) cin >> heights[i];
    cout << getMaxArea(heights) << endl;
    return 0;
}