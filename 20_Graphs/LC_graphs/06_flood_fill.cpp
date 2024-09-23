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
void bfs(vector<vector<int>>& nums, vector<vector<int>>& vis, int i, int j, int newColor) {
    queue<pair<int, int>> q;
    q.push({i, j});
    vis[i][j] = 1;
    int color = nums[i][j];
    nums[i][j] = newColor;
    vector<pair<int, int>> dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    while(!q.empty()) {
        pair<int, int> idx = q.front();
        q.pop();
        for (auto& dir : dirs) {
            int x = dir.first + idx.first;
            int y = dir.second + idx.second;
            if (x>=0 && x<nums.size() && y>=0 && y<nums[0].size() 
                && nums[x][y] == color && vis[x][y] == 0) {
                q.push({x, y});
                vis[x][y] = 1;
                nums[x][y] = newColor;
            }

        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    vector<vector<int>> nums = image;
    int m = nums.size();
    int n = nums[0].size();
    vector<vector<int>> vis(m, vector<int> (n, 0));
    bfs(nums, vis, sr, sc, color);
    cout << "Flood Fill" << endl;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cout << nums[i][j] << " ";
        }
        cout << endl;
    }
    return nums;
}

// Main function
int main() {
    // Start code here
    int m, n;
    cin >> m >> n;
    int sr, sc, color;
    cin >> sr >> sc >> color;

    vector<vector<int>> nums(m, vector<int> (n));

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cin >> nums[i][j];
        }
    }
/*
[[1,1,1],[1,1,0],[1,0,1]]
3 3
1 1 2
1 1 1
1 1 0
1 0 1
*/
    cout << "Matrix" << endl;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cout << nums[i][j] << " ";
        }
        cout << endl;
    }

    nums = floodFill(nums, sr, sc, color);

    return(0);
}