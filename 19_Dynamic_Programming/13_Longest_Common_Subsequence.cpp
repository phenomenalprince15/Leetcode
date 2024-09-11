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

int LCSDPIteration(string& s1, string& s2, int idx1, int idx2, vector<vector<int>>& dp) {


    return 0;
}

int main() {
    string s1 = "ace"

    return 0;
}
 