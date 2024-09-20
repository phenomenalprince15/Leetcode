#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

ll coinRecursive(vector<ll>& nums, ll idx, ll sum) {
    // Base case
    if (sum == 0) return 1;
    if (idx < 0 || sum < 0) return 0;

    int count = 0;
    // Try out all choices
    for (ll i=0; i<nums.size(); i++) {
        count += coinRecursive(nums, i, sum - nums[i]);
    }

    return count;
}

ll coinMemoization(vector<ll>& nums, ll idx, ll sum, vector<vector<ll>>& dp) {
    // Base case
    if (sum == 0) return dp[idx][sum] = 1;
    if (idx < 0 || sum < 0) return 0;

    if (dp[idx][sum] != -1) return dp[idx][sum];

    int count = 0;
    // Try out all choices
    for (ll i=0; i<nums.size(); i++) {
        count = (count + coinMemoization(nums, i, sum - nums[i], dp))%MOD;
    }
    dp[idx][sum] = count;
    return dp[idx][sum];
}

int main() {
    ll n, k;
    cin >> n >> k;

    vector<ll> nums(n);

    for (ll i=0; i<n; i++) {
        cin >> nums[i];
    }

    //cout << coinRecursive(nums, n-1, k) << endl;

    // vector<vector<ll>> dp(n, vector<ll> (k+1, -1));
    // cout << coinMemoization(nums, n-1, k, dp) << endl;
    // for (int i=0; i<=n; i++){
    //     for (int j=0; j<=k; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    // 2D DP counts combinations, not permutations, so either use recursion or 1D DP
    
    // vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));
    // dp[0][0] = 1;
    // for (int i=1; i<=n; i++) {
    //     dp[i][0] = 1;
    // }

    // for (int i=0; i<=k; i++) {
    //     for (ll j=1; j<=n; j++) {
    //         if(i >= nums[j]) dp[j][i] += dp[j-1][i - nums[j]]; //(count + coinMemoization(nums, i, sum - nums[i], dp))%MOD;
    //         dp[j][i] += dp[j-1][i];
    //     }
    // }
    // cout << dp[n][k] << endl;

    // for (int i=0; i<=n; i++){
    //     for (int j=0; j<=k; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return (0);
}
