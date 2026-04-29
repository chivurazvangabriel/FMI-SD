#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        prefix_sum[i] = prefix_sum[i - 1] + val;
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << prefix_sum[r] - prefix_sum[l - 1] << endl;
    }

    return 0;
}