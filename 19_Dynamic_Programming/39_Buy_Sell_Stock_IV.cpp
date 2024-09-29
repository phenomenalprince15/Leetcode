#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Recursive Solution (without memoization)
    int recursiveStock(vector<int>& prices, int idx, int trans, int k) {
        if (idx == prices.size() || trans == k) return 0;

        // Buy stock
        if (trans % 2 == 0) {
            return max(-prices[idx] + recursiveStock(prices, idx + 1, trans + 1, k),
                        recursiveStock(prices, idx + 1, trans, k));
        } else {
            // Sell stock
            return max(prices[idx] + recursiveStock(prices, idx + 1, trans + 1, k),
                        recursiveStock(prices, idx + 1, trans, k));
        }
    }

    // Recursive + Memoization Solution
    int recursiveStockMemo(vector<int>& prices, int idx, int trans, int k, vector<vector<int>>& dp) {
        if (idx == prices.size() || trans == k) return 0;

        if (dp[idx][trans] != -1) return dp[idx][trans];

        // Buy stock
        if (trans % 2 == 0) {
            return dp[idx][trans] = max(-prices[idx] + recursiveStockMemo(prices, idx + 1, trans + 1, k, dp),
                        recursiveStockMemo(prices, idx + 1, trans, k, dp));
        } else {
            // Sell stock
            return dp[idx][trans] = max(prices[idx] + recursiveStockMemo(prices, idx + 1, trans + 1, k, dp),
                        recursiveStockMemo(prices, idx + 1, trans, k, dp));
        }
    }

    // DP Iteration Solution
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 2 * k - 1; j >= 0; j--) {
                // Buy stock
                if (j % 2 == 0) {
                    dp[i][j] = max(-prices[i] + dp[i + 1][j + 1], dp[i + 1][j]);
                } else { // Sell stock
                    dp[i][j] = max(prices[i] + dp[i + 1][j + 1], dp[i + 1][j]);
                }
            }
        }
        return dp[0][0];
    }
};

// Test cases
int main() {
    Solution solution;

    // Test case 1: Basic scenario with 2 transactions
    vector<int> prices1 = {3, 2, 6, 5, 0, 3};
    int k1 = 2;
    cout << "Max Profit (Test case 1): " << solution.maxProfit(k1, prices1) << endl; // Expected: 7

    // Test case 2: All increasing prices
    vector<int> prices2 = {1, 2, 3, 4, 5};
    int k2 = 2;
    cout << "Max Profit (Test case 2): " << solution.maxProfit(k2, prices2) << endl; // Expected: 4

    // Test case 3: All decreasing prices
    vector<int> prices3 = {5, 4, 3, 2, 1};
    int k3 = 3;
    cout << "Max Profit (Test case 3): " << solution.maxProfit(k3, prices3) << endl; // Expected: 0

    // Test case 4: Prices with alternating peaks and valleys
    vector<int> prices4 = {1, 3, 2, 8, 4, 9};
    int k4 = 2;
    cout << "Max Profit (Test case 4): " << solution.maxProfit(k4, prices4) << endl; // Expected: 11

    // Test case 5: Large number of transactions allowed
    vector<int> prices5 = {1, 2, 3, 4, 5};
    int k5 = 10;
    cout << "Max Profit (Test case 5): " << solution.maxProfit(k5, prices5) << endl; // Expected: 4

    return 0;
}
