#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

int recursive(string s, string t, int i, int j) {
    // Base case
    if (j < 0) return 1;
    if (i < 0) return 0;

    // match
    if (s[i] == t[j]) {
        return recursive(s, t, i-1, j-1) +  recursive(s, t, i-1, j);
    }// not match
    return recursive(s, t, i-1, j);
}

int memoization(string s, string t, int i, int j, vector<vector<double>>& dp) {
    // Base case
    if (j < 0) return 1;
    if (i < 0) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    // match
    if (s[i] == t[j]) {
        dp[i][j] = memoization(s, t, i-1, j-1, dp) +  memoization(s, t, i-1, j, dp);
    } else {
        dp[i][j] = memoization(s, t, i-1, j, dp);
    }
    
    return dp[i][j];
}

int numDistinct(string s, string t) {
    int n = s.length();
    int m = t.length();
    cout << recursive(s, t, s.length()-1, t.length()-1) << endl;

    vector<vector<double>> dp(n + 1, vector<double> (m + 1, -1));    
    cout << memoization(s, t, s.length()-1, t.length()-1, dp) << endl;

    // DP Iteration
    dp.assign(n+1, vector<double> (m+1, 0));
    // Base cases
    for (int i=0; i<=n; i++) dp[i][0] = 1;
    for (int j=1; j<=m; j++) dp[0][j] = 0;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m ; j++) {
            if (s[i-1] == t[j-1]) {
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j]; // recursive(s, t, i-1, j-1, dp) +  recursive(s, t, i-1, j, dp);
            } else {
                dp[i][j] = dp[i-1][j]; // recursive(s, t, i-1, j, dp);
            }
        }
    }
    cout << (int)dp[n][m] << endl;

    // Space Optimization
    vector<double> prev(m+1, 0), curr(m+1, 0);
    prev[0] = curr[0] = 1;
    for (int j=1; j<=m; j++) dp[0][j] = 0;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m ; j++) {
            if (s[i-1] == t[j-1]) {
                curr[j] = prev[j-1] + prev[j]; // recursive(s, t, i-1, j-1, dp) +  recursive(s, t, i-1, j, dp);
            } else {
                curr[j] = prev[j]; // recursive(s, t, i-1, j, dp);
            }
        }
        prev = curr;
    }
    cout << "Space Opt." << endl;
    return prev[m];
}

int main() {
    string s, t;
    s = "babgbag";
    t = "bag";

    cout << numDistinct(s, t) << endl;

    return 0;
}