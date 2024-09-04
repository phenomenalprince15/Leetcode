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

        // Pure virtual function to be implemented by derived classes
        virtual int solveRecursive() = 0;
        virtual int solveDPMemoization() = 0;
        virtual int solveDPIteration() = 0;

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
        /*
        Recursion ::
        Think about choices you have.
        prices = [1, 5, 8, 9]
        You can either do a cut of 1 unit, 2 units, 3 units, ..... , L-1 units, L units
        if I do cut of 1 unit, priceSoFar += prices[cut] and work on other subproblem [ |......] similarly repeat
        and take max of all choices.
        f(length) = max{ (cut = 1 to L) prices[cut] + f(L-cut)}
        */

        int maxProfitRecursive(int length) {
            // Base case
            if (length <= 0) return 0;

            int maxProfit = INT_MIN;

            // cut for all choices
            for (int cut=1; cut<=length; cut++) {
                maxProfit = max(maxProfit, prices[cut-1] + maxProfitRecursive(length-cut));
            }
            return maxProfit;
        }
        /*
        TC : O(2^L)
        SC : O(L^2)
        */

        int maxProfitMemoization() {
            return 0;
        }

        int maxProfitDPIteration () {
            return 0;
        }
    
    public:
        RodCutting(vector<int>& prices) : DP(prices.size()), prices(prices), n(prices.size()) {}
        int solveRecursive() {
            return maxProfitRecursive(n);
        }
        int solveDPMemoization() {
            return maxProfitMemoization();
        }
        int solveDPIteration() {
            return maxProfitDPIteration();
        }
};

int main () {
   // Problem 2 
    vector<int> cost = {10, 15, 20, 25, 30};
    MinCostClimbingStairs problem2(cost);

    printf("Minimum cost to reach the top (recursive): %d\n", problem2.solveRecursive());
    printf("Minimum cost to reach the top (memoized): %d\n", problem2.solveDPMemoization());
    printf("Minimum cost to reach the top (iterative): %d\n", problem2.solveDPIteration());

    // Problem 3
    vector<int> prices = {1, 5, 8, 9};
    RodCutting problem3(prices);

    printf("Maximum profit (recursive): %d\n", problem3.solveRecursive());
    printf("Maximum profit (memoized): %d\n", problem3.solveDPMemoization());
    printf("Maximum profit (iterative): %d\n", problem3.solveDPIteration());

    return 0;
}
