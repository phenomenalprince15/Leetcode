#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
#include <string>
#include <cstring>
#include <queue>
#include <stack>

const long long MOD = 1000000007;

using namespace std;

class Solution {
public:
    int recursive(string s, string p, int i, int j) {
        // Base cases
        if (i<0 && j<0) return true;
        if (i>=0 && j<0) return false;
        if (i<0 && j>=0) {
            // check all stars
            for (int x=0; x<=j; x++) {
                if (p[x] != '*') return false;
            }
            return true;
        }

        // match
        if (s[i] == p[j] || p[j] == '?') {
            return recursive(s, p, i-1, j-1);
        }

        // not match  but it's a *
        if (s[i] != p[j] && p[j] == '*') {
            return recursive(s, p, i-1, j) || recursive(s, p, i, j-1);
        }

        // not match at all it's not a *
        return false;
    }

    int memoization(string s, string p, int i, int j, vector<vector<int>>& dp) {
        // Base cases
        if (i<0 && j<0) return true;
        if (i>=0 && j<0) return false;
        if (i<0 && j>=0) {
            // check all stars
            for (int x=0; x<=j; x++) {
                if (p[x] != '*') return false;
            }
            return true;
        }

        if (dp[i][j] != -1) return dp[i][j];

        // match
        if (s[i] == p[j] || p[j] == '?') {
            return dp[i][j] = memoization(s, p, i-1, j-1, dp);
        }

        // not match  but it's a *
        if (s[i] != p[j] && p[j] == '*') {
            return dp[i][j] = memoization(s, p, i-1, j, dp) || memoization(s, p, i, j-1, dp);
        }

        // not match at all it's not a *
        return dp[i][j] = false;
    }

    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        // return recursive(s, p, n-1, m-1);
        vector<vector<int>> dp(n, vector<int> (m, -1));
        // return memoization(s, p, n-1, m-1, dp);

        dp.assign(n+1, vector<int> (m+1, 0));
        // Base case
        dp[0][0] = 1;
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1]; // Empty string can match with '*' pattern
            }
        }
        // match
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (s[i-1] == p[j-1] || p[j-1] == '?') {
                    dp[i][j] = dp[i-1][j-1]; // = memoization(s, p, i-1, j-1, dp);
                }
                // not match  but it's a *
                else if (s[i-1] != p[j-1] && p[j-1] == '*') {
                    dp[i][j] = dp[i-1][j] || dp[i][j-1]; // memoization(s, p, i-1, j, dp) || memoization(s, p, i, j-1, dp);
                }
                // not match at all it's not a *
                else {
                    dp[i][j] = false;
                }
            }
        }
        return dp[n][m];
    }
};

int main() {
    Solution solution;

    // Test Case 1
    string s1 = "aa";
    string p1 = "a";
    cout << "Test Case 1: " << (solution.isMatch(s1, p1) ? "Match" : "No Match") << endl;
    // Expected Output: No Match

    // Test Case 2
    string s2 = "aa";
    string p2 = "*";
    cout << "Test Case 2: " << (solution.isMatch(s2, p2) ? "Match" : "No Match") << endl;
    // Expected Output: Match

    // Test Case 3
    string s3 = "cb";
    string p3 = "?a";
    cout << "Test Case 3: " << (solution.isMatch(s3, p3) ? "Match" : "No Match") << endl;
    // Expected Output: No Match

    return 0;
}
