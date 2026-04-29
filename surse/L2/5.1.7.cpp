#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;

    string result = "";
    for (char c : s) {
        bool found = false;
        for (int i = 0; i < result.size(); i++) {
            if (result[i] == c) {
                result.erase(i, 1);
                found = true;
                break;
            }
        }
        if (!found) {
            result += c;
        }
    }

    cout << result << endl;
    return 0;
}