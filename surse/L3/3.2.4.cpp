#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<long long> hash_vals(n + 1);

    mt19937_64 rng(1337);
    for (int i = 0; i <= n; i++) hash_vals[i] = rng();

    vector<long long> prefix_xor(n + 1, 0);
    vector<long long> target_xor(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        prefix_xor[i + 1] = prefix_xor[i] ^ hash_vals[a[i]];
    }
    for (int i = 0; i <= n; i++) {
        target_xor[i] = (i == 0) ? hash_vals[0] : target_xor[i - 1] ^ hash_vals[i];
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        long long current_range_xor = prefix_xor[r + 1] ^ prefix_xor[l];
        if (current_range_xor == target_xor[r - l]) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}