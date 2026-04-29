#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 9;
const ll BASE = 31;

bool check(int length, const vector<string>& strings) {
    if (length == 0) return true;

    unordered_map<ll, int> global_counts;
    ll p_len = 1;
    for (int i = 0; i < length - 1; i++) p_len = (p_len * BASE) % MOD;

    for (int i = 0; i < strings.size(); i++) {
        const string& s = strings[i];
        if (s.length() < length) return false;

        unordered_set<ll> seen_in_this_string;
        ll current_hash = 0;

        for (int j = 0; j < length; j++) {
            current_hash = (current_hash * BASE + (s[j] - '0' + 1)) % MOD;
        }
        seen_in_this_string.insert(current_hash);

        for (int j = length; j < s.length(); j++) {
            current_hash = (current_hash - (s[j - length] - '0' + 1) * p_len % MOD + MOD) % MOD;
            current_hash = (current_hash * BASE + (s[j] - '0' + 1)) % MOD;
            seen_in_this_string.insert(current_hash);
        }

        for (ll h : seen_in_this_string) {
            global_counts[h]++;
        }
    }

    for (auto const& [hash, count] : global_counts) {
        if (count == strings.size()) return true;
    }

    return false;
}

int main() {
    int n;
    cin >> n;
    vector<string> strings(n);
    int min_len = 1e9;

    for (int i = 0; i < n; i++) {
        cin >> strings[i];
        min_len = min(min_len, (int)strings[i].length());
    }

    int low = 0, high = min_len, ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, strings)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << ans << endl;
    return 0;
}