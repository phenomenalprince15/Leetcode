#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

/*
s = axyb
t = abyxb

==> axb or ayb

-- Find the maximum common LCS
-- Trace back the DP table to find string.

*/

string LCSRecusive(string& s, string& t, int i, int j) {
    // Base case
    if (i < 0 || j < 0) return ""; // return empty string

    // Choose if it matches or not
    // if it matches in both
    if (s[i] == t[j]) {
        return s[i] + LCSRecusive(s, t, i-1, j-1); // add when it matches
    }

    // If it doesn't match explore from both sides
    string subSeq1 = LCSRecusive(s, t, i-1, j);
    string subSeq2 = LCSRecusive(s, t, i, j-1);

    return (subSeq1.length() > subSeq2.length()) ? subSeq1 : subSeq2;
}

string LCSMemoization(string& s, string& t, int i, int j, vector<vector<string>>& dp) {
    // Base case
    if (i < 0 || j < 0) return ""; // return empty string

    // Choose if it matches or not
    // if it matches in both
    if (s[i] == t[j]) {
        return s[i] + LCSRecusive(s, t, i-1, j-1); // add when it matches
    } else {
        // If it doesn't match explore from both sides
        string subSeq1 = LCSRecusive(s, t, i-1, j);
        string subSeq2 = LCSRecusive(s, t, i, j-1);

        dp[i][j] = (subSeq1.length() > subSeq2.length()) ? subSeq1 : subSeq2;
    }

    return dp[i][j];
}

string LCSDPIteration(string& s, string& t) {
    int m = s.length();
    int n = t.length();

    // DP table to store lengths of LCS
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i-1] == t[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;  // Match found
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);  // Take the max from either excluding s[i] or t[j]
            }
        }
    }

    // Reconstruct LCS from the DP table
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s[i-1] == t[j-1]) {
            lcs += s[i-1];  // Include this character in the LCS
            i--, j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;  // Move upwards in the table
        } else {
            j--;  // Move left in the table
        }
    }

    // The LCS is built backwards, so we reverse it
    reverse(lcs.begin(), lcs.end());

    return lcs;
}


int main() {

    string s, t;

    cin >> s >> t;
    int m = s.length();
    int n = t.length();

    //vector<vector<string>> dp(m, vector<string> (n, ""));

    string res = LCSDPIteration(s, t);
    cout << res << endl;

    return 0;
}
