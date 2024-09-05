#include <iostream>
#include <vector>

using namespace std;

class DP {
    protected:
        vector<int> dp;
    
    public:
        // Constructor
        DP (int size) {
            dp = vector<int> (size, -1);
        }

        // Reset the DP table
        void reset(int size) {
            dp.assign(size, -1);
        }
};

class DP2D {
    protected:
        vector<vector<int>> dp2D;
        int n, m;

    public:
        // Constructor
        DP2D(int rows, int cols) : dp2D(rows, vector<int>(cols, -1)), n(rows), m(cols) {}

        // Reset the DP table
        void reset(int rows, int cols) {
            dp2D.assign(rows, vector<int>(cols, -1));
            n = rows;
            m = cols;
        }
};

/*
- Problem 1 (Fibonacci series)
*/

/*
- Problem 2 (Minimum steps for climbing stairs)
- Given an array cost where cost[i] represents the cost of stepping on the i-th step, the goal is to find the minimum cost to reach
the top of the stairs. You can start from either step 0 or step 1 and can move either one step or two steps at a time.

OR

- You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.
You can either start from the step with index 0, or the step with index 1.
Return the minimum cost to reach the top of the floor.

- Example 1:

Input: cost = [10,15,20]
Output: 15
Explanation: You will start at index 1.
- Pay 15 and climb two steps to reach the top.
The total cost is 15.
Example 2:

Input: cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
Explanation: You will start at index 0.
- Pay 1 and climb two steps to reach index 2.
- Pay 1 and climb two steps to reach index 4.
- Pay 1 and climb two steps to reach index 6.
- Pay 1 and climb one step to reach index 7.
- Pay 1 and climb two steps to reach index 9.
- Pay 1 and climb one step to reach the top.
The total cost is 6.

*/
class MinCostClimbingStairs : public DP {
    private:
        vector<int> cost;
        int n;
    
    public:
        MinCostClimbingStairs(vector<int>& cost) : DP(cost.size()), cost(cost), n(cost.size()) {}

        int minimumCostRecursive(int idx) {
            if (idx == 0) return cost[0];
            if (idx == 1) return cost[1];

            int left = minimumCostRecursive(idx - 1) + cost[idx];
            int right = minimumCostRecursive(idx - 2) + cost[idx];
            
            return min(left, right);
        }

        int minimumCostMemoization(int idx) {
            if (idx == 0) return cost[0];
            if (idx == 1) return cost[1];

            if (dp[idx] != -1) return dp[idx];

            int left = minimumCostRecursive(idx - 1) + cost[idx];
            int right = minimumCostRecursive(idx - 2) + cost[idx];
            dp[idx] = min(left, right);
            return dp[idx];
        }

        int minimumCostIteration() {
            dp[0] = cost[0];
            dp[1] = cost[1];

            for (int i = 2; i < dp.size(); ++i) {
                dp[i] = min(dp[i - 1] + cost[i], dp[i - 2] + cost[i]);
            }
            // Cost to reach the top
            return min(dp[dp.size() - 1], dp[dp.size() - 2]);
        }

        int solveRecursive() {
            return min(minimumCostRecursive(n - 1), minimumCostRecursive(n - 2));
        }

        int solveDPMemoization() {
            return min(minimumCostMemoization(n - 1), minimumCostMemoization(n - 2));
        }

        int solveDPIteration() {
            return minimumCostIteration();
        }
};

/*
- Problem 3 (Cutting rod length for maximum profit)
Given:

1. A rod of length n.
2. An array price[] of size n where price[i] represents the price of a rod of length i+1.
The task is to find the maximum profit obtainable by cutting the rod and selling the pieces.

Example
Suppose you have a rod of length 4 and the prices for each length are as follows:

price[] = {1, 5, 8, 9}
This means:

A rod of length 1 has a price of 1.
A rod of length 2 has a price of 5.
A rod of length 3 has a price of 8.
A rod of length 4 has a price of 9.
To get the maximum profit, you could:

Cut the rod into two pieces of length 2 and 2, which would yield a total price of 5 + 5 = 10.
Alternatively, you could cut the rod into four pieces of length 1, which would yield a total price of 1 + 1 + 1 + 1 = 4.
The maximum profit in this example would be 10.
*/

class RodCutting : public DP {
    private:
        vector<int> prices;
        int n;

        int maxProfitRecursive(int length) {
            if (length <= 0) return 0;

            int maxProfit = INT_MIN;
            for (int cut = 1; cut <= length; cut++) {
                maxProfit = max(maxProfit, prices[cut - 1] + maxProfitRecursive(length - cut));
            }
            return maxProfit;
        }

        int maxProfitMemoization(int length) {
            if (length <= 0) return 0;
            if (dp[length - 1] != -1) return dp[length - 1];

            int maxProfit = INT_MIN;
            for (int cut = 1; cut <= length; cut++) {
                maxProfit = max(maxProfit, prices[cut - 1] + maxProfitMemoization(length - cut));
            }
            dp[length - 1] = maxProfit;
            return dp[length - 1];
        }

        int maxProfitDPIteration() {
            dp.resize(n + 1, -1);
            dp[0] = 0;

            for (int i = 1; i <= n; i++) {
                int maxProfit = INT_MIN;
                for (int cut = 1; cut <= i; cut++) {
                    maxProfit = max(maxProfit, prices[cut - 1] + dp[i - cut]);
                }
                dp[i] = maxProfit;
            }

            return dp[n];
        }
    
    public:
        RodCutting(vector<int>& prices) : DP(prices.size()), prices(prices), n(prices.size()) {}

        int solveRecursive() {
            return maxProfitRecursive(n);
        }

        int solveDPMemoization() {
            return maxProfitMemoization(n);
        }

        int solveDPIteration() {
            return maxProfitDPIteration();
        }
};

/*
- Problem 4 : House Robber
Problem:
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed. However, you cannot rob two adjacent houses, as it will alert the police.
Your task is to find the maximum amount of money you can rob tonight without alerting the police.

Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9), rob house 5 (money = 1).
Total amount robbed = 2 + 9 + 1 = 12.
*/
class HouseRobber : public DP {
    private:
        vector<int> houses;
        int n;
    
    public:
        HouseRobber(vector<int>& nums) : houses(nums), n(nums.size()), DP(nums.size()) {}

        /*
        Recursive : Pick or not Pick and think about previous houses and take max of all choices.
        */
        int maxAmountRecursive(int idx) {
            if (idx < 0) return 0;
            if (idx == 0) return houses[0];

            int pick = houses[idx] + maxAmountRecursive(idx - 2);
            int notPick = maxAmountRecursive(idx - 1);

            return max(pick, notPick);
        }

        int maxAmountMemoization(int idx) {
            if (idx < 0) return 0;
            if (idx == 0) return houses[0];
            
            if (dp[idx] != -1) return dp[idx];

            int pick = houses[idx] + maxAmountMemoization(idx - 2);
            int notPick = maxAmountMemoization(idx - 1);
            dp[idx] = max(pick, notPick);

            return dp[idx];
        }

        int solveRecursive() {
            return maxAmountRecursive(n - 1);
        }
        int solveMemoization() {
            return maxAmountMemoization(n-1);
        }
        int solveDPIteration() {
            
            // Base case
            dp[0] = houses[0];
            dp[1] = max(houses[0], houses[1]);

            for (int i=2; i<n; i++) {
                int pick = houses[i] + dp[i-2];
                int notPick = dp[i-1];
                dp[i] = max(pick, notPick);
            }
            return dp[n-1];
        }
};

int main () {
   // Problem 2: MinCostClimbingStairs
    vector<int> cost = {10, 15, 20, 25, 30};
    MinCostClimbingStairs problem2(cost);

    printf("Minimum cost to reach the top (recursive): %d\n", problem2.solveRecursive());
    printf("Minimum cost to reach the top (memoized): %d\n", problem2.solveDPMemoization());
    printf("Minimum cost to reach the top (iterative): %d\n", problem2.solveDPIteration());

    // Problem 3: RodCutting
    vector<int> prices = {1, 5, 8, 9};
    RodCutting problem3(prices);

    printf("Maximum profit (recursive): %d\n", problem3.solveRecursive());
    printf("Maximum profit (memoized): %d\n", problem3.solveDPMemoization());
    printf("Maximum profit (iterative): %d\n", problem3.solveDPIteration());

    // Problem 4: HouseRobber
    vector<int> houses = {2, 7, 9, 3, 1};
    HouseRobber problem4(houses);

    printf("Maximum money robbed (recursive): %d\n", problem4.solveRecursive());
    printf("Maximum money robbed (recursive): %d\n", problem4.solveMemoization());
    printf("Maximum money robbed (recursive): %d\n", problem4.solveDPIteration());

    return 0;
}
