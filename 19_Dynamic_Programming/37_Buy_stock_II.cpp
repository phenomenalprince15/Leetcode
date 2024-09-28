#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Recursive approach (for testing, uncomment return statement in maxProfit)
    int recursive(vector<int>& prices, int idx, int buy) {
        if (idx == prices.size()) return 0;
        if (buy) {
            return max(-prices[idx] + recursive(prices, idx + 1, 0), 
                        recursive(prices, idx + 1, 1));
        } else {
            return max(prices[idx] + recursive(prices, idx + 1, 1), 
                        recursive(prices, idx + 1, 0));
        }
    }

    // Memoization approach (for testing, uncomment return statement in maxProfit)
    int memoization(vector<int>& prices, int idx, int buy, vector<vector<int>>& dp) {
        if (idx == prices.size()) return 0;
        if (dp[idx][buy] != -1) return dp[idx][buy];
        if (buy) {
            dp[idx][buy] = max(-prices[idx] + memoization(prices, idx + 1, 0, dp), 
                        memoization(prices, idx + 1, 1, dp));
        } else {
            dp[idx][buy] = max(prices[idx] + memoization(prices, idx + 1, 1, dp), 
                        memoization(prices, idx + 1, 0, dp));
        }
        return dp[idx][buy];
    }

    // Iterative DP approach (default in maxProfit)
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        dp[n][0] = 0;
        dp[n][1] = 0;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= 1; j++) {
                if (j) {
                    dp[i][j] = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
                } else {
                    dp[i][j] = max(prices[i] + dp[i + 1][1], dp[i + 1][0]);
                }
            }
        }
        return dp[0][1];
    }
};

int main() {
    Solution solution;

    // Test Case 1: Simple Case
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "Test Case 1: " << solution.maxProfit(prices1) << endl; // Expected Output: 7 (Buy at 1, Sell at 6, Buy at 3, Sell at 4)

    // Test Case 2: Increasing Prices
    vector<int> prices2 = {1, 2, 3, 4, 5};
    cout << "Test Case 2: " << solution.maxProfit(prices2) << endl; // Expected Output: 4 (Buy at 1, Sell at 5)

    // Test Case 3: Decreasing Prices
    vector<int> prices3 = {7, 6, 4, 3, 1};
    cout << "Test Case 3: " << solution.maxProfit(prices3) << endl; // Expected Output: 0 (No transactions should be made)

    // Test Case 4: Fluctuating Prices
    vector<int> prices4 = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
    cout << "Test Case 4: " << solution.maxProfit(prices4) << endl; // Expected Output: 15 (Buy at 1, Sell at 4, Buy at 2, Sell at 7, Buy at 2, Sell at 9)

    // Test Case 5: Single Day
    vector<int> prices5 = {5};
    cout << "Test Case 5: " << solution.maxProfit(prices5) << endl; // Expected Output: 0 (No transactions can be made)

    return 0;
}
