#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

/*
https://leetcode.com/problems/longest-common-subsequence/description/

Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

Example 1:

Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.

-----------------------------------------------------
Approach - Think of creating all subsequences and try to look for each of them in each other.
- OR think of Recurision and compare along the way.


                            {abcde} | {ace} starting from end
                                    |
                                    | matching, means we found a letter which matches, we can count it in out length
                            {abcd}  | {ac}
                                    |
                                    | not matching, we can two was, either keep checking with same letter or not.
                    {abc} {ac}             {abcd} {a}   
                        |                        |
                        | match                  | not match
                    {ab} {a}             {abc}{a}   {abcd}{}
like this, it will continue, when we found a match, increase the length, if we couldn't find, max(choice 1, choice 2)
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
    string s1 = "abcde";
    string s2 = "ace";
    int m = s1.length();
    int n = s2.length();

    vector<vector<int>> dp(m, vector<int> (n, -1));
    cout << LCSRecursive(s1, s2, s1.length()-1, s2.length()-1) << endl;
    cout << LCSMemoization(s1, s2, s1.length()-1, s2.length()-1, dp) << endl;
    cout << LCSDPIteration(s1, s2, dp) << endl;

    return 0;
}
 