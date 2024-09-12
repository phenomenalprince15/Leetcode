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

/*
- Leetcode 91 : Decode ways
A message containing letters from A-Z can be encoded into numbers using the following mapping:
'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
To decode a string s consisting of digits, you need to determine how many ways you can decode it.

For example:
"12" can be decoded as "AB" (1 2) or "L" (12). Thus, there are 2 ways to decode it.
"226" can be decoded as "BBF" (2 2 6), "BZ" (2 26), or "VF" (22 6). Thus, there are 3 ways to decode it.
*/
class DecodeWays : public DP {
    private:
        string str;
        int n;
    
    public:
        DecodeWays(string& s) : str(s), n(s.size()), DP(s.size() + 1) {}

        // Recursive approach
        int decodeRecursive(int idx) {
            if (idx == n) return 1;  // Reached end of string
            if (str[idx] == '0') return 0;  // Invalid starting character

            // Choosing one letter
            int count = decodeRecursive(idx + 1);

            // Choosing two letters, between "10" and "26"
            if (idx + 1 < n && (str[idx] == '1' || (str[idx] == '2' && str[idx + 1] <= '6'))) {
                count += decodeRecursive(idx + 2);
            }
            return count;
        }

        // Memoization approach
        int decodeMemoization(int idx) {
            if (idx == n) return 1;  // Reached end of string
            if (str[idx] == '0') return 0;  // Invalid starting character

            if (dp[idx] != -1) return dp[idx];

            // Choosing one letter
            int count = decodeMemoization(idx + 1);

            // Choosing two letters, between "10" and "26"
            if (idx + 1 < n && (str[idx] == '1' || (str[idx] == '2' && str[idx + 1] <= '6'))) {
                count += decodeMemoization(idx + 2);
            }
            dp[idx] = count;
            return count;
        }

        // Dynamic Programming Iteration approach
        int decodeDPIteration() {
            vector<int> dp(n + 1, 0);

            // Base case
            dp[0] = 1;  // An empty string has one way to decode
            if (n > 0) dp[1] = (str[0] != '0') ? 1 : 0;  // Single character can be decoded if it's not '0'

            // Fill the DP table
            for (int i = 1; i < n; ++i) {
                // Check if the single character can be decoded
                if (str[i] != '0') {
                    dp[i + 1] += dp[i];
                }

                // Check if the two characters can be decoded
                if (i > 0 && (str[i - 1] == '1' || (str[i - 1] == '2' && str[i] <= '6'))) {
                    dp[i + 1] += dp[i - 1];
                }
            }

            return dp[n];
        }
};

/*
Unique Path - https://leetcode.com/problems/unique-paths/
*/

/*
Unique Path with obstacles - https://leetcode.com/problems/unique-paths-ii/description/  
*/

/*
Minimum path sum - https://leetcode.com/problems/minimum-path-sum/description/
*/

/*
Minimum Path sum in triangle - https://leetcode.com/problems/triangle/description/
*/

/*
Falling path sum - 
*/

/*
- Problem Description : Subset Sum equals K
You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’.
Your task is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.
Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.

For Example :
If ‘ARR’ is {1,2,3,4} and ‘K’ = 4, then there exists 2 subsets with sum = 4. These are {1,3} and {4}. Hence, return true.

--> Think of problem in terms of generating subsets while reducing target and if it hits zero, it's true, else false.
*/

class SubsetSumEqualsK : public DP2D {
    private:
        vector<int> nums;
        int n;
        int k; // target
    public:
        SubsetSumEqualsK(vector<int>& nums, int target) : nums(nums), k(target), n(nums.size()), DP2D(nums.size(), target) {} 

        bool subsetSumKRecursive(int idx, int target) { // target will decrease or not decrease, choose that
            // Base case
            if (target == 0) return true;
            if (idx == 0) {
                if (target == nums[0]) return true;
                return false;
            }

            // I will be able to take sum only if target >= nums[idx], so it can either be true or false
            //bool takeSum = subsetSumKRecursive(idx - 1, target - nums[idx]); // target will reduce in next step 
            bool takeSum = false;
            if (target >= nums[idx]) {
                takeSum = subsetSumKRecursive(idx - 1, target - nums[idx]);
            }
            
            bool notTakeSum = subsetSumKRecursive(idx - 1, target); // target will remain same in next step

            return takeSum || notTakeSum;
        }

        bool subsetSumKMemoization(int idx, int target) { // target will decrease or not decrease, choose that
            // Base case
            if (target == 0) return true;
            if (idx == 0) {
                if (target == nums[0]) return true;
                return false;
            }

            if (dp2D[idx][target] != -1) return dp2D[idx][target];

            // I will be able to take sum only if target >= nums[idx], so it can either be true or false
            //bool takeSum = subsetSumKRecursive(idx - 1, target - nums[idx]); // target will reduce in next step 
            bool takeSum = false;
            if (target >= nums[idx]) {
                takeSum = subsetSumKMemoization(idx - 1, target - nums[idx]);
            }
            
            bool notTakeSum = subsetSumKMemoization(idx - 1, target); // target will remain same in next step

            dp2D[idx][target] = takeSum || notTakeSum;

            return dp2D[idx][target];
        }

        bool subsetSumKDPIteration () { // target will decrease or not decrease, choose that
            // Think of base case when target is zero, populate all target 0 as dp[idx][target] as true.
            // Think of base case when idx is zero, target is true only when target == nums[0], set as true.
            vector<vector<bool>> dp(n, vector<bool> (k + 1, false));

            for (int i=0; i<n; i++) {
                dp[i][0] = true;
            }

            if (k >= nums[0]) dp[0][nums[0]] = true;

            for (int i=1; i<n; i++) {
                for (int j=1; j<=k; j++) {
                    bool takeSum = false;
                    if (j >= nums[i]) {
                    takeSum = dp[i-1][j - nums[i]]; //subsetSumKMemoization(idx - 1, target - nums[idx]);
                }
                
                bool notTakeSum = dp[i-1][j]; //subsetSumKMemoization(idx - 1, target); // target will remain same in next step

                dp[i][j] = takeSum || notTakeSum;
                }
            }
            return dp[n-1][k];
        }
};

/*
- Problem : Partition Equal Subset Sum - https://leetcode.com/problems/partition-equal-subset-sum/
You are given an array 'ARR' of 'N' positive integers.
Your task is to find if we can partition the given array into two subsets such that the sum of elements in both subsets is equal.

For example, let’s say the given array is [2, 3, 3, 3, 4, 5],
then the array can be partitioned as [2, 3, 5], and [3, 3, 4] with equal sum 10.
Follow Up:
Can you solve this using not more than O(S) extra space, where S is the sum of all elements of the given array?

Sample Input 1:
2
6
3 1 1 2 2 1
5
5 6 5 11 6
Sample Output 1:
true
false    
Explanation Of Sample Input 1:
For the first test case, the array can be partitioned as ([2,1,1,1] and [3, 2]) or ([2,2,1], and [1,1,3]) with sum 5.

For the second test case, the array can’t be partitioned.
Sample Input 2:
2
9
2 2 1 1 1 1 1 3 3
6
8 7 6 12 4 5
Sample Output 2:
false
true

--> Think as the above problem, subset sum equals K. Here we just need to divide totalSum/2 and follow same.
*/

/*
Problem - Partition Set Into 2 Subsets With Min Absolute Sum Diff
https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/description/
*/

/*
Count Subsets with Sum K 

*/

/*
Count Partitions with Given Difference
*/

/*
0/1 Knapsack - 
A thief is robbing a store and can carry a maximal weight of W into his knapsack.
There are N items and the ith item weighs wi and is of value vi.
Considering the constraints of the maximum weight that a knapsack can carry,
you have to find and return the maximum value that a thief can generate by stealing items.

Sample Input:
1 
4
1 2 4 5
5 4 8 6
5
Sample Output:
13
*/

class Knapsack : public DP2D {
    private:
        vector<int> weights;
        vector<int> values;
        int bagW;
    public:
        Knapsack(vector<int>& weights, vector<int> values, int bagW) : weights(weights), values(values), 
                    bagW(bagW), DP2D(weights.size(), bagW + 1) {}
        
        int knapsackRecursive(int idx, int bagW) { // idx = n-1
            // Base case
            if (idx == 0) {
                if (bagW >= weights[idx]) return values[idx];
                else return 0;
            }

            // I can choose to take or not take that weight
            int notTake = knapsackRecursive(idx-1, bagW); // no weight to be added, nothing to reduce from bag weight
            int take = INT_MIN; // I can only take if bagW >= weights[idx] and add the value of that idx weight.
            if (bagW >= weights[idx]) take = values[idx] + knapsackRecursive(idx-1, bagW - weights[idx]);

            return max(take, notTake);
        }

        int knapsackMemoization(int idx, int bagW) { // idx = n-1
        // Base case
        if (idx == 0) {
            if (bagW >= weights[idx]) return values[idx];
            else return 0;
        }

        if (dp2D[idx][bagW] != -1) return dp2D[idx][bagW];

        // I can choose to take or not take that weight
        int notTake = knapsackMemoization(idx-1, bagW); // no weight to be added, nothing to reduce from bag weight
        int take = INT_MIN; // I can only take if bagW >= weights[idx] and add the value of that idx weight.
        if (bagW >= weights[idx]) take = values[idx] + 
            knapsackMemoization(idx-1, bagW - weights[idx]);
        
        dp2D[idx][bagW] = max(take, notTake);

        return dp2D[idx][bagW];
    }

        int knapsackDPIteration() { // idx = n-1
        // Base case (convert from memoization)
        int m = weights.size();
        dp2D.assign(m, vector<int> (bagW + 1, 0));
        for (int j=0; j<=bagW; j++) {
            if (j >= weights[0]) {
                dp2D[0][j] = values[0];
            }
        }

        for (int i=1; i<m; i++) {
            for (int j=0; j<=bagW; j++) {
                int notTake = dp2D[i-1][j]; //knapsackMemoization(weights, values, idx-1, bagW, dp); // no weight to be added, nothing to reduce from bag weight
                int take = INT_MIN; // I can only take if bagW >= weights[idx] and add the value of that idx weight.
                if (j >= weights[i]) take = values[i] + 
                    dp2D[i-1][j - weights[i]]; //knapsackMemoization(weights, values, idx-1, bagW - weights[idx], dp);
                
                dp2D[i][j] = max(take, notTake);
            }
        }
        
        return dp2D[m-1][bagW];
    }
};

/*
- Problem - Coin change (Minimum coins to make target amount with infinite supply of coins)
- Link - https://leetcode.com/problems/coin-change/

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

Example :
coins = [1,2,5], amount = 11
Output: 3
*/

int main () {
   // Problem 2: MinCostClimbingStairs
    // vector<int> cost = {10, 15, 20, 25, 30};
    // MinCostClimbingStairs problem2(cost);

    // printf("Minimum cost to reach the top (recursive): %d\n", problem2.solveRecursive());
    // printf("Minimum cost to reach the top (memoized): %d\n", problem2.solveDPMemoization());
    // printf("Minimum cost to reach the top (iterative): %d\n", problem2.solveDPIteration());

    // // Problem 3: RodCutting
    // vector<int> prices = {1, 5, 8, 9};
    // RodCutting problem3(prices);

    // printf("Maximum profit (recursive): %d\n", problem3.solveRecursive());
    // printf("Maximum profit (memoized): %d\n", problem3.solveDPMemoization());
    // printf("Maximum profit (iterative): %d\n", problem3.solveDPIteration());

    // // Problem 4: HouseRobber
    // vector<int> houses = {2, 7, 9, 3, 1};
    // HouseRobber problem4(houses);

    // printf("Maximum money robbed (recursive): %d\n", problem4.solveRecursive());
    // printf("Maximum money robbed (recursive): %d\n", problem4.solveMemoization());
    // printf("Maximum money robbed (recursive): %d\n", problem4.solveDPIteration());

    // // Problem 5: Leetcode 91
    // string s = "226";
    // DecodeWays decoder(s);
    // cout << "Number of ways to decode: " << decoder.decodeRecursive(0) << endl;
    // cout << "Number of ways to decode: " << decoder.decodeMemoization(0) << endl;
    // cout << "Number of ways to decode: " << decoder.decodeDPIteration() << endl;

    // // Problem - Subset Sum equals K
    // vector<int> nums = {1,2,3,4};
    // int target = 4;
    // SubsetSumEqualsK subsetK(nums, target);
    // bool result = subsetK.subsetSumKDPIteration();
    // if (result) {
    //     cout << "Subset sum equals K is true." << endl;
    // } else {
    //     cout << "Subset sum equals K is false." << endl;
    // }

    vector<int> weights = {1, 3, 4, 5};
    vector<int> values = {10, 40, 50, 70};
    int bagW = 8; // Maximum weight the bag can hold

    // Create the Knapsack object
    Knapsack knapsack(weights, values, bagW);

    // Compute the maximum value that can be obtained with the given weight limit
    int n = weights.size();
    int maxValue = knapsack.knapsackDPIteration();

    // Output the result
    cout << "Maximum value that can be obtained: " << maxValue << endl;

    return 0;
}
