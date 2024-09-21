#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

/*
There is a text and pattern. we need to find/search pattern in the given text.
ex : text = "AABAACAADAABAAABAA" -> n
     pattern = "AABA" -> m

Naive approach would be go over the text and keep matching every letter of pattern with text.
if matched, return, else shift pattern to next index of text one by one.
TC - O(n - m + 1) * m

with LPS-KMP algorithm - TC - O(n + m)
*/

void naivePatternSearch(string& text, string& pattern) {
    int n = text.length();
    int m = pattern.length();

    // Loop over every possible string pattern
    for (int i=0; i<= n-m; i++) { // i till n-m
        int count=0;
        for (int j=0; j<m; j++) {
            count++;
            if (pattern[j] != text[i+j]) { // if I am at idx 5 in text, I need to check for 5+0, 5+1, 5+2 ... so on
                break;
            }
        }

        if (count == m) {
            cout << "Pattern found at index: " << i << endl;
        }
    }
}

/*
Calculate LPS array which stores at each index it's longest prefix, which is also a suffix.
ex : abbac
Prefix - a, ab, abb, abba, abbac
Suffix - a, ba, bba, abba, cabba

common - abba = 2 length : which is longest common prefix which is also a suffix and also a palindrome.

*/
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

void searchKMPwithLPS(string& text, string& pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> lps = calculateLPS(pattern);
    
    int i=0, len=0;
    while(i < n) { // to search inside text
        if (text[i] == pattern[len]) {
            i++;
            len++;
        }
        if (len == m) {
            cout << "Pattern found at index: " << i-len << endl;
            len = lps[len-1]; // continue searching other patterns
        } else if (i < n && text[i] != pattern[len]) {
            if (len != 0) {
                len = lps[len-1]; // backtrack until len is 0
            } else {
                i++; // move to next character
            }
        }
    }

    return;
}

int main(int argc, char** argv) {

    string text = "AABAACAADAABAAABAA";
    string pattern = "AABA";
    cout << "Using naive search for pattern" << endl;
    naivePatternSearch(text, pattern);
    
    // Testing LPS
    // string s = "ababcabab";
    // vector<int> lps = calculateLPS(s);
    // for (auto ele : s) cout << ele << " ";
    // cout << endl;
    // for (auto ele : lps) cout << ele << " ";
    // cout << endl;

    // Using LPS to search for pattern
    cout << "Using LPS to search for pattern" << endl;
    searchKMPwithLPS(text, pattern);

    return(0);
}

