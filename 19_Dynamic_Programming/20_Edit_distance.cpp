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

#define ll long long

using namespace std;

// Description
/*
https://leetcode.com/problems/edit-distance/description/

Q. Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

- Insert a character
- Delete a character
- Replace a character

Sol: Thinking Approach, it's string, so try matching and not matching
- we need minimum operations, max could be if we just delete everything and insert or just replace everything.
for minimum ::
- if the letters match, great ---> reduce index from both strings
- if not mtaching, then that's one way (take min of all these 3)
    - 1 + recurse(i-1, j) // delete
    - 1 + recurse(i, j-1) // insert
    - 1 + recurse(i-1, j-1) // replace

*/

// Add functions
int recursiveEditDistance(string& s, string& t, int i, int j) {
    // Base case
    if (i < 0) return j+1; // if s gets "" return whatever is in t, as s can be inserted
    if (j < 0) return i+1; // if t gets "" return whatever is in s, as s can be deleted then

    // match
    if (s[i] == t[j]) return recursiveEditDistance(s, t, i-1, j-1);

    return 1 + min(recursiveEditDistance(s, t, i-1, j), // delete
                min(recursiveEditDistance(s, t, i, j-1), // insert 
                recursiveEditDistance(s, t, i-1, j-1))); // replace
}

int memoizationEditDistance(string& s, string& t, int i, int j, vector<vector<int>>& dp) {
    // Base case
    if (i < 0) return j+1; // if s gets "" return whatever is in t, as s can be inserted
    if (j < 0) return i+1; // if t gets "" return whatever is in s, as s can be deleted then

    if (dp[i][j] != -1) return dp[i][j];

    // match
    if (s[i] == t[j]) return dp[i][j] = memoizationEditDistance(s, t, i-1, j-1, dp);

    return dp[i][j] = 1 + min(memoizationEditDistance(s, t, i-1, j, dp), // delete
                min(memoizationEditDistance(s, t, i, j-1, dp), // insert 
                memoizationEditDistance(s, t, i-1, j-1, dp))); // replace
}

// Main function
int main() {
    ios::sync_with_stdio(false); // Disable synchronization with C I/O for faster I/O
    cin.tie(nullptr); // Untie cin from cout to further improve performance
    // Start code here
    string s = "horse", t = "ros";
    int n = s.length();
    int m = t.length();
    cout << recursiveEditDistance(s, t, n-1, m-1) << endl;

    s = "intention", t = "execution";
    n = s.length();
    m = t.length();
    cout << recursiveEditDistance(s, t, n-1, m-1) << endl;

    // Memoization
    vector<vector<int>> dp(n, vector<int> (m, -1));
    cout << memoizationEditDistance(s, t, n-1, m-1, dp) << endl;

    // DP Iteration
    dp.assign(n+1, vector<int> (m+1, 0));
    // Base case
    for (int i=0; i<=n; i++) dp[i][0] = i;
    for (int j=0; j<=m; j++) dp[0][j] = j;

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            // match
            if (s[i-1] == t[j-1]) dp[i][j] = dp[i-1][j-1];//memoizationEditDistance(s, t, i-1, j-1, dp);
            else dp[i][j] = 1 + min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])); // min(memoizationEditDistance(s, t, i-1, j, dp), // delete
                        // min(memoizationEditDistance(s, t, i, j-1, dp), // insert 
                        // memoizationEditDistance(s, t, i-1, j-1, dp))); // replace
        }
    }

    cout << dp[n][m] << endl;

    return(0);
}