#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

long long countWithAtMost(const vector<int>& a, int k) {
    if (k <= 0) return 0;
    unordered_map<int, int> counts;
    int left = 0;
    long long total = 0;
    for (int right = 0; right < a.size(); right++) {
        counts[a[right]]++;
        while (counts.size() > k) {
            counts[a[left]]--;
            if (counts[a[left]] == 0) counts.erase(a[left]);
            left++;
        }
        total += (right - left + 1);
    }
    return total;
}

int main() {
    int n, l, u;
    cin >> n >> l >> u;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << countWithAtMost(a, u) - countWithAtMost(a, l - 1) << endl;
    return 0;
}