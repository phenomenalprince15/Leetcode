#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

/*
Given a sequence of matrices, find the most efficient way to multiply these matrices together.
The efficient way is the one that involves the least number of multiplications.

The dimensions of the matrices are given in an array arr[] of size N (such that N = number of matrices + 1) 
where the ith matrix has the dimensions (arr[i-1] x arr[i]).

Example:
Input: N = 5
arr = {40, 20, 30, 10, 30}
Output: 26000
Explanation: There are 4 matrices of dimension 
40x20, 20x30, 30x10, 10x30. Say the matrices are 
named as A, B, C, D. Out of all possible combinations,
the most efficient way is (A*(B*C))*D. 
The number of operations are -
20*30*10 + 40*20*10 + 40*10*30 = 26000.
*/

int matrixCMRecursive(int i, int j, vector<int>& nums) {
    if (i == j) return 0; // i starts with 1 and j starts with n-1

    int mini = INT_MAX; // having a minimum at each iteration
    // Try all possible ways fo all cuts (partition)
    for (int cut=i; cut<j; cut++) { // cut i to j-1
        int stepsTaken = (nums[i-1] * nums[cut] * nums[j]) 
                + matrixCMRecursive(i, cut, nums) + matrixCMRecursive(cut+1, j, nums);
        mini = min(mini, stepsTaken);
    }
    return mini;
}

int matrixCMMemoization(int i, int j, vector<int>& nums, vector<vector<int>>& dp) {
    if (i == j) return 0; // i starts with 1 and j starts with n-1

    if (dp[i][j] != -1) return dp[i][j];

    int mini = INT_MAX; // having a minimum at each iteration
    // Try all possible ways fo all cuts (partition)
    for (int cut=i; cut<j; cut++) { // cut i to j-1
        int stepsTaken = (nums[i-1] * nums[cut] * nums[j]) 
                + matrixCMRecursive(i, cut, nums) + matrixCMRecursive(cut+1, j, nums);
        mini = min(mini, stepsTaken);
    }
    dp[i][j] = mini;
    return dp[i][j];
}

int main() {
    
    vector<int> nums = {10, 20, 30, 40, 50};
	int n = nums.size();
	
	cout << matrixCMRecursive(1, n-1, nums) << endl;

    vector<vector<int>> dp(n, vector<int> (n, -1));
    cout << matrixCMMemoization(1, n-1, nums, dp) << endl;

    // DP Iteration
    dp.assign(n, vector<int> (n, 0));

    // Base case: cost is 0 when multiplying one matrix
    for (int i = 1; i < n; i++) dp[i][i] = 0;

    // Iterate over all chain lengths
    for (int len = 2; len < n; len++) {
        for (int i = 1; i <= n - len; i++) { // starting points
            int j = i + len - 1; // ending point
            dp[i][j] = INT_MAX;

            // Try all possible cuts/partitions
            for (int cut = i; cut < j; cut++) {
                int stepsTaken = nums[i - 1] * nums[cut] * nums[j] +
                                 dp[i][cut] + dp[cut + 1][j];
                dp[i][j] = min(dp[i][j], stepsTaken);
            }
        }
    }

    // The result is stored in dp[1][n-1]
    cout << dp[1][n-1] << endl;

    return 0;
}
