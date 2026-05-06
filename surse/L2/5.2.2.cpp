#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct State {
    int v1, v2;
    bool operator<(const State& other) const {
        if (v1 != other.v1) return v1 < other.v1;
        return v2 < other.v2;
    }
};

int main() {
    int a, b, t;
    cin >> a >> b >> t;

    queue<State> q;
    map<State, State> parent;
    map<State, string> action;

    q.push({0, 0});
    parent[{0, 0}] = {-1, -1};

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.v1 == t || curr.v2 == t) {
            cout << "Target reached" << endl;
            return 0;
        }

        vector<pair<State, string>> next_states = {
            {{a, curr.v2}, "Fill 1"},
            {{curr.v1, b}, "Fill 2"},
            {{0, curr.v2}, "Empty 1"},
            {{curr.v1, 0}, "Empty 2"},
            {{max(0, curr.v1 - (b - curr.v2)), min(b, curr.v2 + curr.v1)}, "Pour 1->2"},
            {{min(a, curr.v1 + curr.v2), max(0, curr.v2 - (a - curr.v1))}, "Pour 2->1"}
        };

        for (auto& next : next_states) {
            if (parent.find(next.first) == parent.end()) {
                parent[next.first] = curr;
                action[next.first] = next.second;
                q.push(next.first);
            }
        }
    }

    return 0;
}