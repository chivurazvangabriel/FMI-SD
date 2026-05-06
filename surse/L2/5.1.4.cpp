#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

string removeDuplicates(string s, int k) {
    stack<pair<char, int>> st;

    for (char c : s) {
        if (!st.empty() && st.top().first == c) {
            st.top().second++;
        } else {
            st.push({c, 1});
        }

        if (st.top().second == k) {
            st.pop();
        }
    }

    string result = "";
    while (!st.empty()) {
        for (int i = 0; i < st.top().second; i++) result += st.top().first;
        st.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}