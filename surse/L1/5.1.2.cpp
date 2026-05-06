#include <iostream>
#include <vector>

using namespace std;

void solveTwoSum(vector<int>& a, int s) {
    int left = 0;
    int right = a.size() - 1;

    while (left < right) {
        int current_sum = a[left] + a[right];
        if (current_sum == s) {
            cout << "Indices: " << left << " " << right << endl;
            return;
        } else if (current_sum < s) {
            left++;
        } else {
            right--;
        }
    }
    cout << "No pair found" << endl;
}

int main() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    solveTwoSum(a, s);
    return 0;
}