#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

ll knapsackIRecursive(vector<ll>& weights, vector<ll>& values, ll idx, ll amt) { // idx = n-1
    // Base case
    if(idx < 0) return 0;
    if (amt == 0) return 0;
    if (idx == 0) {
        if (amt >= weights[idx]){
            return values[idx];
        }
        return 0;
    }

    // selecting to take or notTake a coin
    ll notTake = knapsackIRecursive(weights, values, idx-1, amt);
    ll take = LLONG_MIN;
    if (amt >= weights[idx]) {
        take = values[idx] + knapsackIRecursive(weights, values, idx-1, amt - weights[idx]);
    }

    return max(take, notTake);
}

ll knapsackIMemoization(vector<ll>& weights, vector<ll>& values, 
                            vector<vector<ll>>& dp, ll idx, ll amt) { // idx = n-1
    // Base case
    if(idx < 0) return 0;
    if (amt == 0) return 0;
    if (idx == 0) {
        if (amt >= weights[idx]){
            return values[idx];
        }
        return 0;
    }

    if (dp[idx][amt] != -1) return dp[idx][amt];

    // selecting to take or notTake a coin
    ll notTake = knapsackIMemoization(weights, values, dp, idx-1, amt);
    ll take = LLONG_MIN;
    if (amt >= weights[idx]) {
        take = values[idx] + knapsackIMemoization(weights, values, dp, idx-1, amt - weights[idx]);
    }
    dp[idx][amt] = max(take, notTake);

    return dp[idx][amt];
}

ll knapsackIDPIteration(vector<ll>& weights, vector<ll>& values, ll amt) {
    vector<vector<ll>> dp(weights.size(), vector<ll>(amt + 1, 0));
    
    // Base case (convert from memoization)
    for (int j = 0; j <= amt; j++) {
        if (j >= weights[0]) {
            dp[0][j] = values[0];
        }
    }

    for (int i = 1; i < weights.size(); i++) {
        for (int j = 0; j <= amt; j++) {
            ll notTake = dp[i-1][j];
            ll take = LLONG_MIN;
            if (j >= weights[i]) {
                take = values[i] + dp[i-1][j - weights[i]];
            }
            dp[i][j] = max(take, notTake);
        }
    }
    
    return dp[weights.size() - 1][amt];
}

int main() {
    ll n, w;
    cin >> n >> w;

    vector<ll> weights(n);
    vector<ll> values(n);

    for (ll i = 0; i < n; i++) {
        cin >> weights[i] >> values[i];
    }

    // Ensure you use the right function
    cout << knapsackIDPIteration(weights, values, w) << endl;

    return 0;
}
