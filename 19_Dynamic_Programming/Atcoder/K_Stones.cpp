#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

bool canWinRecursive(ll k, vector<ll>& nums) {
    if (k <= 0) return false; // no stones left

    // Try out all winning positions
    for (int i=0; i<nums.size(); i++) {
        if (k >= nums[i]) {
            if (!canWinRecursive(k - nums[i], nums)) {
                return true;
            }
        }
    }

    // found no winning position
    return false;
}

bool canWinMemoization(ll k, vector<ll>& nums, vector<ll>& dp) {
    if (k <= 0) return false; // no moves left

    if (dp[k] != -1) return dp[k];

    for (int i=0; i<nums.size(); i++) {
        if (k >= nums[i]) {
            if (!canWinMemoization(k - nums[i], nums, dp)) {
                return dp[k] = true;
            }
        }
    }

    return dp[k] = false;
}

bool canWinDPIterative(ll k, vector<ll>& nums) {
    vector<bool> dp(k + 1, false);  // Initialize DP table with false, all losing position

    for (ll i = 1; i <= k; ++i) {
        for (ll move : nums) {
            if (i>=move && !dp[i - move]) {
                dp[i] = true; // winning position
                break;  // No need to check further moves
            }
        }
    }

    return dp[k];
}

int main() {
    ll n, k;
    cin >> n >> k;
    vector<ll> nums(n);

    for (ll i=0; i<n; i++) {
        cin >> nums[i];
    }
    
    if (canWinRecursive(k, nums)) {
        cout << "First" << endl;
    } else{
        cout << "Second" << endl;
    }
    
    vector<ll> dp(k+1, -1);
    
    if (canWinMemoization(k, nums, dp)) {
        cout << "First" << endl;
    } else{
        cout << "Second" << endl;
    }
    
    if (canWinDPIterative(k, nums)) {
        cout << "First" << endl;
    } else{
        cout << "Second" << endl;
    }

    return 0;
}

/*
Based on NIM Game
- you can pick from 1 to 3 stones
- one picks last wins

n = 4 always ways
n = 5 win
n = 6 win
n = 7 win
n = 8 always ways
n = 9 win
*/