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
/*
f(nums, x, y) { // x = 0, y = 0;
    // base case
    if (arr is exhaused) return max - min;

    if (PA turns) {
       return  x = max(f(nums, x + nums[start], y) or f(nums, x + nums[end], y))
    }

    if (PB turns) {
        return y = min(f(nums, x, nums[start] + y) or f(nums, x, nums[end] + y))
    }
}
*/

ll f(vector<ll>& nums, ll x, ll y, ll turn, ll start, ll end) {
    // Base case: if there are no elements left
    if (start > end) {
        return x - y; // Return the score difference
    }

    // Player A (Taro's Turn)
    if (turn == 0) {
        // Try taking from the start or the end
        ll takeStart = f(nums, x + nums[start], y, 1, start + 1, end); // Take from start
        ll takeEnd = f(nums, x + nums[end], y, 1, start, end - 1); // Take from end
        return max(takeStart, takeEnd); // Return the maximum score difference for Taro
    } 
    // Player B (Jiro's Turn)
    else {
        // Try taking from the start or the end
        ll takeStart = f(nums, x, y + nums[start], 0, start + 1, end); // Take from start
        ll takeEnd = f(nums, x, y + nums[end], 0, start, end - 1); // Take from end
        return min(takeStart, takeEnd); // Return the minimum score difference for Jiro
    }
}

/*
function (nums, start, end) {
    // Base case


    // if Taro chooses
    ll takeStart = nums[start] - function(nums, start+1, end); // Taro's choice - Jiro's Optimal choice in next round
    ll takeEnd = nums[end] - function(nums, start, end-1); // Same thing here and it repeats

    return max(takeStart, takeEnd)
}
*/

ll game(vector<ll>& nums, ll start, ll end) {
    // Base case
    if (start > end) return 0;

    // if Taro chooses
    ll takeStart = nums[start] - game(nums, start+1, end); // Taro's choice - Jiro's Optimal choice in next round
    ll takeEnd = nums[end] - game(nums, start, end-1); // Same thing here and it repeats

    return max(takeStart, takeEnd);
}

ll gameMemo(vector<ll>& nums, ll start, ll end, vector<vector<ll>>& dp) {
    // Base case
    if (start > end) return 0;

    if (dp[start][end] != -1) return dp[start][end];

    // if Taro chooses
    ll takeStart = nums[start] - game(nums, start+1, end); // Taro's choice - Jiro's Optimal choice in next round
    ll takeEnd = nums[end] - game(nums, start, end-1); // Same thing here and it repeats

    return dp[start][end] = max(takeStart, takeEnd);
}

// Main function
int main() {
    ios::sync_with_stdio(false); // Disable synchronization with C I/O for faster I/O
    cin.tie(nullptr); // Untie cin from cout to further improve performance
    // Start code here
    ll n;
    cin >> n;
    vector<ll> nums(n);
    for (ll i=0; i<n; i++) cin >> nums[i];
    // cout << f(nums, 0, 0, 0, 0, n-1) << endl;

    // cout << game(nums, 0, n-1) << endl;

    vector<vector<ll>> dp(n, vector<ll> (n, -1));
    // cout << gameMemo(nums, 0, n-1, dp) << endl;

/*
Base Case:

For length 1: You can directly set dp[i][i] for all i.
Filling for Length 2:

You would fill dp[0][1], dp[1][2], ..., up to dp[n-2][n-1].
Continuing to Larger Lengths:

When filling for length 3, you would fill dp[0][2], dp[1][3], ..., until dp[n-3][n-1].
ans = dp[0][n-1] in longest subarray formed
*/

    dp.assign(n, vector<ll> (n, 0));
    // Base case
    for (int i = 0; i < n; ++i) {
        dp[i][i] = nums[i]; // If there's only one element, Taro takes it
    }
    
    // Think of all sub-arrays of len 2 and more
    for (int len=2; len<=n; len++) {
        for (int start=0; start<=n-len; start++) {
            int end = start + len - 1;
            // if Taro chooses for winning position
            ll takeStart = nums[start] - dp[start+1][end]; // nums[start] - game(nums, start+1, end); // Taro's choice - Jiro's Optimal choice in next round
            ll takeEnd = nums[end] - dp[start][end-1]; // nums[end] - game(nums, start, end-1); // Same thing here and it repeats

            dp[start][end] = max(takeStart, takeEnd);
        }
    }

    cout << dp[0][n-1] << endl;

    return(0);
}