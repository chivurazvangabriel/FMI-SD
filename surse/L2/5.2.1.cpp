#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point { int x, y; };

int main() {
    int n, m, startX, startY, endX, endY;
    cin >> n >> m >> startX >> startY >> endX >> endY;

    vector<vector<int>> grid(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));

    for (int i = 0; i < m; i++) {
        int r, c;
        cin >> r >> c;
        grid[r][c] = 1;
    }

    queue<Point> q;
    q.push({startX, startY});
    dist[startX][startY] = 1;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.x == endX && curr.y == endY) {
            cout << dist[curr.x][curr.y] << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i], ny = curr.y + dy[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && grid[nx][ny] == 0 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return 0;
}