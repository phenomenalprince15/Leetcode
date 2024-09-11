#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

/*
Problem : https://leetcode.com/problems/coin-change-ii/description/
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.

You may assume that you have an infinite number of each kind of coin.
The answer is guaranteed to fit into a signed 32-bit integer.
Example 1:

Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
Example 2:

Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.
Example 3:

Input: amount = 10, coins = [10]
Output: 1
*/

int coinChangeIIRecursive(vector<int>& coins, int idx, int amt) {
    // Base case
    if (idx == 0) {
        if (amt % coins[idx] == 0) {
            return 1;
        }
        return 0;
    }

    // Choose and not choose
    int notTake = coinChangeIIRecursive(coins, idx - 1, amt);
    int take = 0;
    if (amt >= coins[idx]) take = coinChangeIIRecursive(coins, idx, amt - coins[idx]);

    return take  + notTake;
}

int coinChangeIIMemoization(vector<int>& coins, int idx, int amt, vector<vector<int>>& dp) {
    // Base case
    if (idx == 0) {
        if (amt % coins[idx] == 0) {
            return 1;
        }
        return 0;
    }

    if(dp[idx][amt] != -1) return dp[idx][amt];

    // Choose and not choose
    int notTake = coinChangeIIMemoization(coins, idx - 1, amt, dp);
    int take = 0;
    if (amt >= coins[idx]) take = coinChangeIIMemoization(coins, idx, amt - coins[idx], dp);

    dp[idx][amt] = take + notTake;

    return dp[idx][amt];
}

int coinChangeIIDPIteration(vector<int>& coins, int idx, int amt, vector<vector<int>>& dp) {

    dp.assign(coins.size(), vector<int> (amt + 1, 0));

    for (int j=0; j<=amt; j++) {
        if (j % coins[0] == 0) {
            dp[0][j] = 1;
        } else {
            dp[0][j] = 1;
        }
    }

    for (int i=1; i<coins.size(); i++) {
        for (int j=0; j<=amt; j++) {
            int notTake = dp[i-1][j]; //coinChangeIIMemoization(coins, idx - 1, amt, dp);
            int take = 0;
            if (j >= coins[i]) take = 1 + dp[i-1][j - coins[i]]; //coinChangeIIMemoization(coins, idx, amt - coins[idx], dp);

            dp[i][j] = take + notTake;
        }
    }    

    return dp[coins.size() - 1][amt];
}

int main() {
    int n;
    int amount;
    vector<int> coins(n);
    n = 3, amount = 5;
    coins = {1, 2, 5};

    vector<vector<int>> dp(n, vector<int> (amount + 1, -1));

    cout << coinChangeIIRecursive(coins, n-1, amount) << endl;
    cout << coinChangeIIMemoization(coins, n-1, amount, dp) << endl;
    cout << coinChangeIIMemoization(coins, n-1, amount, dp) << endl;

    return 0;
}