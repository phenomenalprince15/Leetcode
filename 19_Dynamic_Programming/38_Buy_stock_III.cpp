#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int memoization(vector<int>& prices, int idx, int buy, int cap, vector<vector<vector<int>>>& dp) {
        // Base case
        if (cap == 0) return 0;
        if (idx == prices.size()) return 0;

        if (dp[idx][buy][cap] != -1) return dp[idx][buy][cap];

        // buy stock
        if (buy) {
            return dp[idx][buy][cap] = max(-prices[idx] + memoization(prices, idx+1, 0, cap, dp),
                        memoization(prices, idx+1, 1, cap, dp));
        } else {
            return dp[idx][buy][cap] = max(prices[idx] + memoization(prices, idx+1, 1, cap-1, dp),
                        memoization(prices, idx+1, 0, cap, dp));
        }
    }
    
    int recursive(vector<int>& prices, int idx, int buy, int cap) {
        // Base case
        if (cap == 0) return 0;
        if (idx == prices.size()) return 0;

        // buy stock
        if (buy) {
            return max(-prices[idx] + recursive(prices, idx+1, 0, cap),
                        recursive(prices, idx+1, 1, cap));
        } else {
            return max(prices[idx] + recursive(prices, idx+1, 1, cap-1),
                        recursive(prices, idx+1, 0, cap));
        }
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // return recursive(prices, 0, 1, 2);
        // vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (3, -1)));
        // return memoization(prices, 0, 1, 2, dp);

        // dp.assign(n+1, vector<vector<int>> (2, vector<int> (3, 0)));
        // dp[n][0][0] = 0;
        // dp[n][1][0] = 0;
        // for (int i=n-1; i>=0; i--) {
        //     for (int j=0; j<=1; j++) {
        //         for (int k=1; k<=2; k++) {
        //             if (j==1) {
        //                 dp[i][j][k] = max(-prices[i] + dp[i+1][0][k],
        //                             dp[i+1][1][k]);
        //             } else {
        //                 dp[i][j][k] = max(prices[i] + dp[i+1][1][k-1],
        //                             dp[i+1][0][k]);
        //             }
        //         }
        //     }
        // }
        // return dp[0][1][2];

        // Anothe method
        // return recursiveStock(prices, 0, 0);
        vector<vector<int>> dp(n, vector<int> (4, -1));
        // return recursiveStockMemo(prices, 0, 0, dp);

        // DP Iteration
        dp.assign(n+1, vector<int> (5, 0));

        for (int i=n-1; i>=0; i--) {
            for (int j=3; j>=0; j--){
                // buy stock
                if (j%2 == 0) {
                    dp[i][j] = max(-prices[i] + dp[i+1][j+1],
                                dp[i+1][j]);
                } else {
                    dp[i][j] = max(prices[i] + dp[i+1][j+1],
                                dp[i+1][j]);
                }
            }
        }
        return dp[0][0];
    }

    // Another way::
/*
keep a track of transactions happening - B S B S ......
Buy will happen when even and Sell will happen when it's odd
*/    
    int recursiveStock(vector<int>& prices, int idx, int trans) {
        // Base case
        if (idx == prices.size() || trans == 4) return 0;

        // buy stock
        if (trans%2 == 0) {
            return max(-prices[idx] + recursiveStock(prices, idx+1, trans+1),
                        recursiveStock(prices, idx+1, trans));
        } else {
            return max(prices[idx] + recursiveStock(prices, idx+1, trans+1),
                        recursiveStock(prices, idx+1, trans));
        }
    }

    int recursiveStockMemo(vector<int>& prices, int idx, int trans, vector<vector<int>>& dp) {
        // Base case
        if (idx == prices.size() || trans == 4) return 0;

        if (dp[idx][trans] != -1) return dp[idx][trans];

        // buy stock
        if (trans%2 == 0) {
            return dp[idx][trans] = max(-prices[idx] + recursiveStockMemo(prices, idx+1, trans+1, dp),
                        recursiveStockMemo(prices, idx+1, trans, dp));
        } else {
            return dp[idx][trans] = max(prices[idx] + recursiveStockMemo(prices, idx+1, trans+1, dp),
                        recursiveStockMemo(prices, idx+1, trans, dp));
        }
    }

};

int main() {
    Solution solution;

    // Test Case 1
    vector<int> prices1 = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "Test Case 1: " << solution.maxProfit(prices1) << endl;
    // Expected output: 6 (Buy on day 4 at 0, sell on day 6 at 3, buy on day 7 at 1, sell on day 8 at 4)

    // Test Case 2
    vector<int> prices2 = {1, 2, 3, 4, 5};
    cout << "Test Case 2: " << solution.maxProfit(prices2) << endl;
    // Expected output: 4 (Buy on day 1 at 1, sell on day 5 at 5)

    // Test Case 3
    vector<int> prices3 = {7, 6, 4, 3, 1};
    cout << "Test Case 3: " << solution.maxProfit(prices3) << endl;
    // Expected output: 0 (No transactions are done)

    // Test Case 4
    vector<int> prices4 = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
    cout << "Test Case 4: " << solution.maxProfit(prices4) << endl;
    // Expected output: 13 (Buy on day 1 at 1, sell on day 3 at 4, buy on day 7 at 2, sell on day 9 at 9)

    // Test Case 5
    vector<int> prices5 = {};
    cout << "Test Case 5: " << solution.maxProfit(prices5) << endl;
    // Expected output: 0 (No prices available)

    return 0;
}