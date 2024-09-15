#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

int recursive(vector<int>& nums, int idx, int sum) {
    // Base case
    if (idx == 0) {
        if (sum % nums[idx] == 0) return sum/nums[idx];
        return INT_MAX;
    }
    if (sum < 0) return INT_MAX;

    // take or not take
    int notTake = recursive(nums, idx-1, sum);
    int take = INT_MAX;
    if (sum >= nums[idx]) {
        int res = recursive(nums, idx, sum - nums[idx]);
        if (res != INT_MAX) take = 1 + res;
    }

    return min(take, notTake);
}

int memoization(vector<int>& nums, int idx, int sum, vector<vector<int>>& dp) {
    // Base case
    if (idx == 0) {
        if (sum % nums[idx] == 0) return sum/nums[idx];
        return INT_MAX;
    }
    if (sum < 0) return INT_MAX;

    if (dp[idx][sum] != -1) return dp[idx][sum];
    // take or not take
    int notTake = memoization(nums, idx-1, sum, dp);
    int take = INT_MAX;
    if (sum >= nums[idx]) {
        int res = memoization(nums, idx, sum - nums[idx], dp);
        if (res != INT_MAX) take = 1 + res;
    }
    dp[idx][sum] = min(take, notTake);
    return dp[idx][sum];
}

int main() {
    ios::sync_with_stdio(false); // Disable synchronization with C I/O for faster I/O
    cin.tie(nullptr); // Untie cin from cout to further improve performance

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i=0; i<n; i++) {
        cin >> nums[i];
    }

    // int res = recursive(nums, n-1, k);
    // if(res == INT_MAX) cout << -1 << endl;
    // cout << res << endl;

    vector<vector<int>> dp(n, vector<int> (k+1, -1));
    // int res = memoization(nums, n-1, k, dp);
    // if(res == INT_MAX) cout << -1 << endl;
    // else cout << res << endl;

    // DP Iteration
    dp.assign(n, vector<int> (k+1, INT_MAX));

    // if idx is zero, then amount is checked with amt/nums[0]
    for (int j=0; j<=k; j++) {
        if (j%nums[0] == 0) dp[0][j] = j/nums[0];
    }

    for (int i=1; i<n; i++) {
        for (int j=0; j<=k; j++) {
            int notTake = dp[i-1][j]; //memoization(nums, i-1, j, dp);
            int take = INT_MAX;
            if (j >= nums[i]) {
                int res = dp[i][j-nums[i]]; //memoization(nums, i, j - nums[i], dp);
                if (res != INT_MAX) take = 1 + res;
            }
            dp[i][j] = min(take, notTake);           
        }
    }
    if(dp[n-1][k] == INT_MAX) cout << -1 << endl;
    else cout << dp[n-1][k] << endl;

    return 0;
}