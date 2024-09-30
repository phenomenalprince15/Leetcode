#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Cooldown
*/

class Solution {
public:
    int recursive(vector<int>& prices, int idx, int buy) {
        // Base case
        if (idx >= prices.size()) return 0;

        // time to buy
        if (buy) {
            return max(-prices[idx] + recursive(prices, idx + 1, 0), 
                       recursive(prices, idx + 1, 1));
        } else {
            return max(prices[idx] + recursive(prices, idx + 2, 1), 
                       recursive(prices, idx + 1, 0));
        }
    }

    int memoization(vector<int>& prices, int idx, int buy, vector<vector<int>>& dp) {
        // Base case
        if (idx >= prices.size()) return 0;

        if (dp[idx][buy] != -1) return dp[idx][buy];

        // time to buy
        if (buy) {
            dp[idx][buy] = max(-prices[idx] + memoization(prices, idx + 1, 0, dp), 
                               memoization(prices, idx + 1, 1, dp));
        } else {
            dp[idx][buy] = max(prices[idx] + memoization(prices, idx + 2, 1, dp), 
                               memoization(prices, idx + 1, 0, dp));
        }
        return dp[idx][buy];
    }

    int maxProfit(vector<int>& prices) {
        // Uncomment to use recursive approach
        // return recursive(prices, 0, 1);

        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        // Base case
        dp[n][0] = 0;
        dp[n][1] = 0;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= 1; j++) {
                if (j) {
                    dp[i][j] = max(-prices[i] + dp[i + 1][0], 
                                   dp[i + 1][1]);
                } else {
                    dp[i][j] = max(prices[i] + dp[i + 2][1], 
                                   dp[i + 1][0]);
                }
            }
        }
        return dp[0][1];
    }
};

int main() {
    Solution solution;

    // Test cases
    vector<vector<int>> testCases = {
        {7, 1, 5, 3, 6, 4},   // Expected profit: 7
        {1, 2, 3, 4, 5},      // Expected profit: 4
        {7, 6, 4, 3, 1},      // Expected profit: 0
        {1, 2, 3},            // Expected profit: 2
        {2, 1, 2, 1, 2}       // Expected profit: 2
    };

    for (const auto& prices : testCases) {
        cout << "Prices: ";
        for (int price : prices) {
            cout << price << " ";
        }
        cout << "-> Max Profit: " << solution.maxProfit(prices) << endl;
    }

    return 0;
}
