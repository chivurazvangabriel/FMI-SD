#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& a, int left, int right) {
    int pivot = a[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (a[j] <= pivot) {
            swap(a[i], a[j]);
            i++;
        }
    }
    swap(a[i], a[right]);
    return i;
}

int quickSelect(vector<int>& a, int left, int right, int k) {
    if (left <= right) {
        int pivotIndex = partition(a, left, right);
        if (pivotIndex == k - 1) return a[pivotIndex];
        if (pivotIndex > k - 1) return quickSelect(a, left, pivotIndex - 1, k);
        return quickSelect(a, pivotIndex + 1, right, k);
    }
    return -1;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << quickSelect(a, 0, n - 1, k) << endl;
    return 0;
}