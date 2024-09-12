#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

/*
Given a string s. In one step you can insert any character at any index of the string.
Return the minimum number of steps to make s palindrome.
A Palindrome String is one that reads the same backward as well as forward.

Example 1:

Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we do not need any insertions.
Example 2:

Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".
Example 3:

Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".
*/

int LCSRecursive(string& s1, string& s2, int idx1, int idx2) {
    // Base case
    if (idx1 < 0 || idx2 < 0) return 0;

    // Choose the indexes
    // If matches, then count++ and reduce indexes
    if (s1[idx1] == s2[idx2]) {
        return 1 + LCSRecursive(s1, s2, idx1-1, idx2-1);
    }

    // If it doesn't match, then act on both indexes separately and return max of both
    return max(LCSRecursive(s1, s2, idx1-1, idx2), LCSRecursive(s1, s2, idx1, idx2-1));
}

int LCSMemoization(string& s1, string& s2, int idx1, int idx2, vector<vector<int>>& dp) {
    // Base case
    if (idx1 < 0 || idx2 < 0) return 0;

    // Choose the indexes
    // If matches, then count++ and reduce indexes
    if (s1[idx1] == s2[idx2]) {
        return 1 + LCSRecursive(s1, s2, idx1-1, idx2-1);
    }

    // If it doesn't match, then act on both indexes separately and return max of both
    return max(LCSRecursive(s1, s2, idx1-1, idx2), LCSRecursive(s1, s2, idx1, idx2-1));

    return 0;
}

int LCSDPIteration(string& s1, string& s2, vector<vector<int>>& dp) {
    int m = s1.size();
    int n = s2.size();

    dp.assign(m+1, vector<int> (n+1, 0));
    
    // Base case
    //if (idx1 < 0 || idx2 < 0) return 0;
    for (int i = 0; i<= m; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j<= n; j++) {
        dp[0][j] = 0;
    }

    // Choose the indexes
    // If matches, then count++ and reduce indexes
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1]; //return dp[idx1][idx2] = 1 + LCSMemoization(s1, s2, idx1-1, idx2-1, dp);
            }else {
                // If it doesn't match, then act on both indexes separately and return max of both
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]); //max(LCSMemoization(s1, s2, idx1-1, idx2, dp), LCSMemoization(s1, s2, idx1, idx2-1, dp));
            }
        }
    }
    return dp[m][n];
}

int main() {
    string s1 = "mbadm";
    string s2 = s1;
    reverse(s2.begin(), s2.end());
    int m = s1.length();
    int n = s2.length();

    vector<vector<int>> dp(m, vector<int> (n, -1));
    cout << m - LCSRecursive(s1, s2, s1.length()-1, s2.length()-1) << endl;
    cout << m - LCSMemoization(s1, s2, s1.length()-1, s2.length()-1, dp) << endl;
    cout << m - LCSDPIteration(s1, s2, dp) << endl;

    return 0;
}
 