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
void bfsIslands(vector<vector<int>>& nums, vector<vector<int>>& vis, int i, int j) {
    queue<pair<int, int>> q;
    q.push({i, j});
    vis[i][j] = 1;

    while(!q.empty()) {
        pair<int, int> idx;
        idx.first = q.front().first;
        idx.second = q.front().second;
        q.pop();

        // Travel in all 8 directions to find islands
        for (int row=-1; row<=1; row++) {
            for (int col=-1; col<=1; col++) {
                int x = idx.first + row; // new row
                int y = idx.second + col; // new col
                if (x < nums.size() && y < nums[0].size() &&
                    x >= 0 && y >= 0
                    && !vis[x][y] && nums[x][y] == 1) {
                        q.push({x, y});
                        vis[x][y] = 1;
                    }
            }
        }
    }

    return;
}

// Main function
int main() {
    // Start code here
    /*
    grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]

5 4
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1
    */

    int m, n;
    cin >> m >> n;

    vector<vector<int>> nums(m, vector<int> (n));

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cin >> nums[i][j];
        }
    }

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cout << nums[i][j] << " ";
        }
        cout << endl;
    }

    vector<vector<int>> vis(m, vector<int> (n, 0));
    int countIslands = 0;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (vis[i][j] == 1 || nums[i][j] == 0) continue;
            countIslands++;
            bfsIslands(nums, vis, i, j);
        }
    }
    cout << countIslands << endl;

    return(0);
}