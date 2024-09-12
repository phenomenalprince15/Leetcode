#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

/*
You are given two strings str1 and str2. Your task is to find the length of the longest common substring among the given strings.

Examples:

Input: str1 = "ABCDGH", str2 = "ACDGHR"
Output: 4
Explanation: The longest common substring is "CDGH" which has length 4.
Input: str1 = "ABC", str2 = "ACB"
Output: 1
Explanation: The longest common substrings are "A", "B", "C" all having length 1.

Recursive Approach :: 
                    abcdgh | acdghr
                    /               \
                   /                  \
            abcdg | acdghr         abcdgh | acdgh

if matches then increase count
if not matches, try both possibilities with count as 0
take currCount as local for function to get the maximum overall.
*/

int LCSRecursive(string& s1, string& s2, int idx1, int idx2, int count) {
    // Base case
    if (idx1 < 0 || idx2 < 0) return count;

    int currCount = count;
    // Choose the indexes
    // If matches, then count++ and reduce indexes
    if (s1[idx1] == s2[idx2]) {
        currCount = LCSRecursive(s1, s2, idx1-1, idx2-1, count + 1);
    }

    // If it doesn't match, then act on both indexes separately and return max of both
    currCount = max({currCount, LCSRecursive(s1, s2, idx1-1, idx2, 0), LCSRecursive(s1, s2, idx1, idx2-1, 0)});

    return currCount;
}

int LCSMemoization(string& s1, string& s2, int idx1, int idx2, vector<vector<int>>& dp, int count) {
    // Base case
    if (idx1 < 0 || idx2 < 0) return 0;

    int currCount = count;
    // Choose the indexes
    // If matches, then count++ and reduce indexes
    if (s1[idx1] == s2[idx2]) {
        currCount = LCSMemoization(s1, s2, idx1-1, idx2-1, dp, count + 1);
    }

    // If it doesn't match, then act on both indexes separately and return max of both
    currCount = max({currCount, LCSMemoization(s1, s2, idx1-1, idx2, dp, 0), LCSMemoization(s1, s2, idx1, idx2-1, dp, 0)});

    return currCount;
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

    int maxAns = INT_MIN;

    // Choose the indexes
    // If matches, then count++ and reduce indexes
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1]; //return dp[idx1][idx2] = 1 + LCSMemoization(s1, s2, idx1-1, idx2-1, dp);
                maxAns = max(maxAns, dp[i][j]);
            }else {
                // If it doesn't match
                //dp[i][j] = max(dp[i-1][j], dp[i][j-1]); //max(LCSMemoization(s1, s2, idx1-1, idx2, dp), LCSMemoization(s1, s2, idx1, idx2-1, dp));
                dp[i][j] = 0;
            }
        }
    }
    return (maxAns == INT_MIN) ? 0 : maxAns;;
}

int main() {
    string s1 = "ABCDGH";
    string s2 = "ACDGHR";
    int m = s1.length();
    int n = s2.length();

    vector<vector<int>> dp(m, vector<int> (n, -1));
    cout << LCSRecursive(s1, s2, s1.length()-1, s2.length()-1, 0) << endl;
    cout << LCSMemoization(s1, s2, s1.length()-1, s2.length()-1, dp, 0) << endl;
    cout << LCSDPIteration(s1, s2, dp) << endl;

    return 0;
}
 