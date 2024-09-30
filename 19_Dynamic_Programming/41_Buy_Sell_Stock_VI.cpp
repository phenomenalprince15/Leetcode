/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int recursive(vector<int>& prices, int idx, int buy, int fee) {
        // Base case
        if (idx == prices.size()) return 0;

        // time to buy
        if (buy) {
            return max(-prices[idx] + recursive(prices, idx + 1, 0, fee), 
                       recursive(prices, idx + 1, 1, fee));
        } else {
            return max(prices[idx] + recursive(prices, idx + 1, 1, fee) - fee, 
                       recursive(prices, idx + 1, 0, fee));
        }
    }

    int memoization(vector<int>& prices, int idx, int buy, vector<vector<int>>& dp, int fee) {
        // Base case
        if (idx == prices.size()) return 0;

        if (dp[idx][buy] != -1) return dp[idx][buy];

        // time to buy
        if (buy) {
            dp[idx][buy] = max(-prices[idx] + memoization(prices, idx + 1, 0, dp, fee), 
                               memoization(prices, idx + 1, 1, dp, fee));
        } else {
            dp[idx][buy] = max(prices[idx] + memoization(prices, idx + 1, 1, dp, fee) - fee, 
                               memoization(prices, idx + 1, 0, dp, fee));
        }
        return dp[idx][buy];
    }

    int maxProfit(vector<int>& prices, int fee) {
        // Uncomment to use the recursive approach
        // return recursive(prices, 0, 1, fee);

        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        // Base case
        for (int i = n; i >= 0; i--) {
            for (int j = 0; j <= 1; j++) {
                if (i == n) {
                    dp[i][j] = 0;  // No transactions possible at the end
                } else if (j) {
                    dp[i][j] = max(-prices[i] + dp[i + 1][0], 
                                   dp[i + 1][1]);
                } else {
                    dp[i][j] = max(prices[i] + dp[i + 1][1] - fee, 
                                   dp[i + 1][0]);
                }
            }
        }
        return dp[0][1];
    }
};

int main() {
    Solution solution;

    // Test cases with different fees
    vector<pair<vector<int>, int>> testCases = {
        {{7, 1, 5, 3, 6, 4}, 1},   // Expected profit: 7 - 1 = 6
        {{1, 2, 3, 4, 5}, 1},      // Expected profit: 4 - 1 = 3
        {{7, 6, 4, 3, 1}, 1},      // Expected profit: 0
        {{1, 2, 3}, 1},            // Expected profit: 2 - 1 = 1
        {{2, 1, 2, 1, 2}, 1}       // Expected profit: 2 - 1 = 1
    };

    for (const auto& test : testCases) {
        const vector<int>& prices = test.first;
        int fee = test.second;
        cout << "Prices: ";
        for (int price : prices) {
            cout << price << " ";
        }
        cout << " | Fee: " << fee << " -> Max Profit: " << solution.maxProfit(prices, fee) << endl;
    }

    return 0;
}
