#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
#include <string>
#include <cstring>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

// Add functions
vector<int> calculateLPS(string& s) {
    int n = s.length();
    vector<int> lps(n, 0);
    lps[0] = 0;

    int i=1, len=0;
    while (i < n) {
        if (s[i] == s[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) { // if not matching, backtrack until len gets to 0.
                len = lps[len-1];
            } else { // nothing available to backtrack, so lps[i] = 0
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

string shortestPalindrome(string& new_s, string& s, string& rev_s) {
    int n = new_s.length();
    vector<int> lps = calculateLPS(new_s);

    int len = rev_s.length() - lps[n-1];
    string prefix = "";
    // for (int i=0; i<len; i++) {
    //     prefix += rev_s[i];
    // }
    prefix = rev_s.substr(0, len);

    return prefix + s;
}

// Main function
int main() {
    // Start code here
    string s = "abbac";
    string rev_s = string(s.rbegin(), s.rend());

    string new_s = s + '#' + rev_s;
    cout << shortestPalindrome(new_s, s, rev_s);

    return 0;
}