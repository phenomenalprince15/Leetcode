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
/*
https://leetcode.com/problems/rotting-oranges/description/

Make sure to go simulataneously.
*/

// Add functions
void bfs(queue<pair<pair<int, int>, int>>& q, vector<vector<int>>& nums, vector<vector<int>>& vis, int* t) {
    vector<pair<int, int>> dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

    while(!q.empty()) {
        pair<pair<int, int>, int> idx = q.front();
        q.pop();
        // go in four directions
        for (auto& dir : dirs) {
            int x = idx.first.first + dir.first;
            int y = idx.first.second + dir.second;
            int time = idx.second;
            if (x>=0 && x<nums.size() && y>=0 && y<nums[0].size()
                && vis[x][y] == 0 && nums[x][y] == 1) {
                    vis[x][y] = 2;
                    nums[x][y] = 2;
                    q.push({{x, y}, time + 1});
                    *t = max(*t, time + 1);
                }
        }
    }

    //cout << t << endl;
    return;
}

int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> nums = grid;
    vector<vector<int>> vis(m, vector<int> (n, 0));
    int t=0;
    queue<pair<pair<int, int>, int>> q;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (nums[i][j] == 2) {
                q.push({{i, j}, 0});
            }
        }
    }
    bfs(q, nums, vis, &t);
    // for (int i=0; i<m; i++) {
    //     for (int j=0; j<n; j++) {
    //         if (vis[i][j] == 0 && nums[i][j] == 2) {
    //             bfs(nums, vis, i, j, &t);
    //         }
    //     }
    // }

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (nums[i][j] == 1) return -1;
        }
    }

    return t;
}

// Main function
int main() {
    // Start code here
    int m, n;
    cin >> m >> n;

    vector<vector<int>> nums(m, vector<int> (n));

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cin >> nums[i][j];
        }
    }

    cout << "Matrix" << endl;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cout << nums[i][j] << " ";
        }
        cout << endl;
    }
/*
grid = [[2,1,1],[1,1,0],[0,1,1]]
3 3
2 1 1
1 1 0
0 1 1
op - 4
*/
    cout << orangesRotting(nums) << endl;

    return(0);
}