#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve3Sum(vector<int>& a, int s) {
    int n = a.size();
    sort(a.begin(), a.end());

    for (int i = 0; i < n - 2; i++) {
        int target = s - a[i];
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = a[left] + a[right];
            if (sum == target) {
                cout << a[i] << " " << a[left] << " " << a[right] << endl;
                return;
            } else if (sum < target) left++;
            else right--;
        }
    }
}