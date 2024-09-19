#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

int main(){
    ll n; // n flowers
    cin >> n;

    vector<ll> heightsOfFlowers(n), beautiesOfFlowers(n);

    for(int i=0; i<n; i++) {
        cin >> heightsOfFlowers[i];
    }

    for(int i=0; i<n; i++){
        cin >> beautiesOfFlowers[i];
    }

    vector<ll> dp(n);
    // Initialize dp with beauties of flowers, that could be maximum so far for each flower
    for (int i=0; i<n; i++) dp[i] = beautiesOfFlowers[i];

    ll sum = 0; // maxBeauty
    for(ll i=1; i<n; i++) {
        for(ll j=0; j<i; j++) {
            if (heightsOfFlowers[i] > heightsOfFlowers[j]) {
                // dp[i] = max(dp[i], 1 + dp[j]); // instead of longest increasing length,
                // store the longest increasing beauty in dp table
                dp[i] = max(dp[i], dp[j] + beautiesOfFlowers[i]);
            }
        }
        // dp[i] represents the maxBeauty so far of a subsequence
        sum = max(sum, dp[i]); // get the max beauty so far in increasing subsequence
    }
    cout << sum << endl;

    // TC : O(n*n)

    // To reduce TC to O(log n) use segment tree or fenwick tree

    return 0;
}