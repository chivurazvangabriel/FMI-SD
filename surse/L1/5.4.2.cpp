#include <iostream>

using namespace std;

long long integerSquareRoot(long long n) {
    if (n < 2) return n;
    long long left = 1, right = n / 2;
    long long ans = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (mid <= n / mid) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

int main() {
    long long n;
    cin >> n;
    cout << integerSquareRoot(n) << endl;
    return 0;
}