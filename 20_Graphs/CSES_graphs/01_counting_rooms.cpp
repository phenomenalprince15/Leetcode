#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
#include <string>
#include <cstring>
#include <queue>
#include <stack>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

// Description


// Add functions
void bfs(vector<vector<char>>& nums, vector<vector<int>>& vis, int i, int j) {
    vis[i][j] = 1;
    queue<pair<int, int>> q;
    q.push({i, j});

    vector<pair<int, int>> dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    while(!q.empty()) {
        pair<int, int> idx = q.front();
        q.pop();
        for (auto& dir : dirs) {
            int x = idx.first + dir.first;
            int y = idx.second + dir.second;
            if (x>=0 && x<nums.size() && y>=0 && y<nums[0].size()
                && vis[x][y] == 0 && nums[x][y] == '.') {
                    q.push({x, y});
                    vis[x][y] = 1;
                }
        }
    }

    return;
}

// Main function
int main() {
    // Start code here
    int m, n;
    cin >> m >> n;

    vector<vector<char>> nums(m, vector<char> (n));

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cin >> nums[i][j];
        }
    }
    // cout << "Matrix" << endl;
    // for (int i=0; i<m; i++) {
    //     for (int j=0; j<n; j++) {
    //         cout << nums[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int countRooms = 0;
    vector<vector<int>> vis(m, vector<int> (n, 0));
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (vis[i][j] == 0 && nums[i][j] == '.') {
                countRooms++;
                bfs(nums, vis, i, j);
            }
        }
    }
    cout << countRooms << endl;

    return(0);
}