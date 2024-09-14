#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

int gridIRecursiveMemo(vector<string>& nums, int i, int j, vector<vector<int>>& dp) {
    // Base case
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    
    if (dp[i][j] != -1) return dp[i][j];

    // Blocked path
    if (nums[i][j] == '#') return 0;

    // choose or not choose path
    int top = gridIRecursiveMemo(nums, i-1, j, dp);
    int left = gridIRecursiveMemo(nums, i, j-1, dp);
    dp[i][j] = (top + left) % MOD;

    return dp[i][j];
}

int main() {
    int rows, cols;
    cin >> rows >> cols;

    vector<string> grid(rows);
    
    // Input the grid row by row
    for (int i = 0; i < rows; i++) {
        cin >> grid[i];  // Input each row as a string
    }

    // Example output to verify grid input
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         cout << grid[i][j] << " ";  // Print each character with space
    //     }
    //     cout << endl;
    // }

    vector<vector<int>> dp (rows, vector<int> (cols, -1));
    //cout << (gridIRecursiveMemo(grid, rows-1, cols-1, dp)) <<  endl;

    // DP Iteration way
    dp.assign(rows  + 1, vector<int> (cols + 1, 0));
    dp[0][0] = 1;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            // choose or not choose path
            if (i == 0 && j == 0) continue;
            if (grid[i][j] == '#') {
                dp[i][j] = 0;
            } else{
                int left = 0, top = 0;
                if (i > 0) top = dp[i-1][j];
                if (j > 0) left = dp[i][j-1];
                dp[i][j] = (left + top) % MOD;
            }
        }
    }
    cout << dp[rows-1][cols-1] << endl;

    return 0;
}