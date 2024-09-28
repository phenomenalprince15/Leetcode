#include <iostream>
#include <vector>
#include <algorithm> // for max and min functions
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // On day 0th
        int mini = prices[0];
        int profit = 0;

        for (int i = 1; i < prices.size(); i++) {
            profit = max(profit, prices[i] - mini);
            mini = min(mini, prices[i]);
        }
        return profit;
    }
};

int main() {
    Solution solution;
    
    // Example 1
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "Max Profit (Example 1): " << solution.maxProfit(prices1) << endl;
    // Output: 5

    // Example 2
    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << "Max Profit (Example 2): " << solution.maxProfit(prices2) << endl;
    // Output: 0

    // Example 3
    vector<int> prices3 = {1, 2, 3, 4, 5};
    cout << "Max Profit (Example 3): " << solution.maxProfit(prices3) << endl;
    // Output: 4

    return 0;
}
