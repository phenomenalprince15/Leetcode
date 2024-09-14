#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

// Keep track of current Index and previous Index
int LISRecursive(vector<int>& nums, int idx, int prev_idx) {
    // Base case
    if (idx == nums.size()) return 0;

    // Choose or not choose index
    int notTake = LISRecursive(nums, idx + 1, prev_idx);
    int take = 0;
    if (prev_idx == -1 || nums[idx] > nums[prev_idx]) {
        take = 1 + LISRecursive(nums, idx + 1, idx); // prev index becomes new index
    }

    return max(take, notTake);
}

int LISMemoization(vector<int>& nums, int idx, int prev_idx, vector<vector<int>>& dp) {
    // Base case
    if (idx == nums.size()) return 0;

    if (dp[idx][prev_idx + 1] != -1) return dp[idx][prev_idx + 1]; // add 1 to prev_idx as it could be -1 also

    // Choose or not choose index
    int notTake = LISMemoization(nums, idx + 1, prev_idx, dp);
    int take = 0;
    if (prev_idx == -1 || nums[idx] > nums[prev_idx]) {
        take = 1 + LISMemoization(nums, idx + 1, idx, dp); // prev index becomes new index
    }
    dp[idx][prev_idx+1] = max(take, notTake);

    return dp[idx][prev_idx + 1];
}

int main() {
    vector<int> nums = {10,9,2,5,3,7,101,18};
    int n = nums.size();

    vector<vector<int>> dp(n, vector<int> (n+1, -1));
    cout << LISRecursive(nums, 0, -1) << endl;
    cout << LISMemoization(nums, 0, -1, dp) << endl;

    // DP Iteration, Think about indexes
    // idx -> n-1 to 0 and prev_idx -> n-1 to 0 ? no, -1 <= prev_idx <= idx-1
    dp.assign(n+1, vector<int> (n+1, 0));

    for (int idx=n-1; idx>=0; idx--) {
        for (int prev_idx=idx-1; prev_idx>=-1; prev_idx--) {
            // Choose or not choose index
            int notTake = dp[idx+1][prev_idx+1]; //LISMemoization(nums, idx + 1, prev_idx, dp);
            int take = 0;
            if (prev_idx == -1 || nums[idx] > nums[prev_idx]) {
                take = 1 + dp[idx+1][idx+1]; //1 + LISMemoization(nums, idx + 1, idx, dp); // prev index becomes new index
            }
            dp[idx][prev_idx+1] = max(take, notTake);
        }
    }
    cout << dp[0][0] << endl;

    // Print LIS
    // nums = {10,9,2,5,3,7,101,18}
    vector<int> dp1(n, 1);

    for(int idx=1; idx<n; idx++) {
        for (int prev_idx=0; prev_idx<=idx-1; prev_idx++) {
            if (nums[idx] > nums[prev_idx]) {
                dp1[idx] = max(1 + dp1[prev_idx], dp1[idx]); // Take only max of curr and prev to ensure longest is taken
            }
        }
    }
    cout << *max_element(dp1.begin(), dp1.end()) << endl;

    for (auto ele : dp1) cout << ele << " ";
    cout << endl;

    // Print LIS
    // nums = {10,9,2,5,3,7,101,18}
    dp1.assign(n, 1);
    vector<int> storeIdx(n);
    for (int i=0; i<n; i++) {
        storeIdx[i] = i;
    }

    for(int idx=1; idx<n; idx++) {
        for (int prev_idx=0; prev_idx<=idx-1; prev_idx++) {
            if (nums[idx] > nums[prev_idx]) {
                //dp1[idx] = max(1 + dp1[prev_idx], dp1[idx]); // Take only max of curr and prev to ensure longest is taken
                if (1 + dp1[prev_idx] > dp1[idx]) {
                    dp1[idx] = 1 + dp1[prev_idx];
                    storeIdx[idx] = prev_idx;
                }
            }
        }
    }
    cout << *max_element(dp1.begin(), dp1.end()) << endl;

    for (auto ele : dp1) cout << ele << " ";
    cout << endl;

    for (auto ele : storeIdx) cout << ele << " ";
    cout << endl;

    // To get the index where maximum value occurs
    int lisEndIdx = max_element(dp1.begin(), dp1.end()) - dp1.begin();
    // Now backtrack the storeIdx list and print LIS
    vector<int> lis;
    while (storeIdx[lisEndIdx] != lisEndIdx) { // traverse till both index gets equal
        lis.push_back(nums[lisEndIdx]);
        lisEndIdx = storeIdx[lisEndIdx];
    }
    lis.push_back(nums[lisEndIdx]); // Add the last element

    // The reconstructed LIS is in reverse order, so reverse it
    reverse(lis.begin(), lis.end());

    for (auto ele : lis) cout << ele << " ";
    cout << endl;

    return 0;
}