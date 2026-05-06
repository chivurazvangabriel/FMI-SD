#include <iostream>
#include <vector>

using namespace std;

void searchMatrix(vector<vector<int>>& m, int x) {
    int n = m.size();
    int row = 0;
    int col = n - 1;

    while (row < n && col >= 0) {
        if (m[row][col] == x) {
            cout << "Found at: " << row << " " << col << endl;
            return;
        } else if (m[row][col] > x) {
            col--;
        } else {
            row++;
        }
    }
    cout << "Not found" << endl;
}

int main() {
    int n, x;
    cin >> n >> x;
    vector<vector<int>> m(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> m[i][j];
    searchMatrix(m, x);
    return 0;
}