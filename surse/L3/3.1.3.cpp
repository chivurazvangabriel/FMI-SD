#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long ll;

struct RollingHash {
    ll base = 31;
    ll mod = 1e9 + 9;

    ll compute(const string& s) {
        ll h = 0;
        for (char c : s) {
            h = (h * base + (c - 'a' + 1)) % mod;
        }
        return h;
    }
};