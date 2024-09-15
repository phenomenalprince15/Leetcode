#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <fstream>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

// int recursive(vector<int>& nums, int currIdx, int prevIdx) {
//     // Base case
//     if (currIdx == nums.size()) return 0;

//     // choose or not choose currIdx
//     int notTake = recursive(nums, currIdx+1, prevIdx);
//     int take = INT_MIN;
//     if(prevIdx == -1 || nums[currIdx] > nums[prevIdx]) {
//         take = 1 + recursive(nums, currIdx+1, currIdx);
//     }

//     return max(take, notTake);
// }

// int memoization(vector<int>& nums, int currIdx, int prevIdx, vector<vector<int>>& dp) {
//     // Base case
//     if (currIdx == nums.size()) return 0;

//     if (dp[currIdx][prevIdx + 1] != -1) return dp[currIdx][prevIdx + 1];

//     // choose or not choose currIdx
//     int notTake = memoization(nums, currIdx+1, prevIdx, dp);
//     int take = INT_MIN;
//     if(prevIdx == -1 || nums[currIdx] > nums[prevIdx]) {
//         take = 1 + memoization(nums, currIdx+1, currIdx, dp);
//     }
//     dp[currIdx][prevIdx+1] = max(take, notTake);

//     return dp[currIdx][prevIdx+1];
// }

int main() {
    ios::sync_with_stdio(false); // Disable synchronization with C I/O for faster I/O
    cin.tie(nullptr); // Untie cin from cout to further improve performance

    ll n;
    cin >> n;

    vector<ll> nums(n);
    for (ll i=0; i<n; i++) {
        cin >> nums[i];
    }

    //cout << recursive(nums, 0, -1) << endl;
    //vector<vector<ll>> dp(n, vector<ll> (n+1, -1));
    //cout << memoization(nums, 0, -1, dp) << endl; 

    //DP Iteratino
    // dp.assign(n+1, vector<ll> (n+1, 0));
    // // Recursion -> 0 to n and -1 to currIdx
    // for(ll currIdx=n-1; currIdx>=0; currIdx--){
    //     for(ll prevIdx=currIdx-1; prevIdx>=-1; prevIdx--){
    //         ll notTake = dp[currIdx+1][prevIdx+1]; //memoization(nums, currIdx+1, prevIdx, dp);
    //         ll take = 0;
    //         if(prevIdx == -1 || nums[currIdx] > nums[prevIdx]) {
    //             take = 1 + dp[currIdx+1][currIdx+1]; //1 + memoization(nums, currIdx+1, currIdx, dp);
    //         }
    //         dp[currIdx][prevIdx+1] = max(take, notTake);
    //     }
    // }
    // cout << dp[0][0] << endl;

    // DP Iteration is still O(n*n) not good for large values.

    // Using Binary search + Patience Sort
    vector<int> top(n, 0);
    int piles = 0;

    for (int i=0; i<n; i++) {
        int card = nums[i];
        int lo=0, hi=piles;

        // Top contains, all top elements. (Top doesn't mean maximum)
        // It's the smallest than previous number inside of it, we can only enter number smaller the top element
        // So, all piles having top element is the smallest in that pile, but right piles number is bigger
        // Search element in top, in which pile I can put it with binary search.
        while (lo < hi) {
            int mid = (lo + hi)/2;
            if (top[mid] > card) hi=mid;
            else if (top[mid] < card) lo = mid+1;
            else hi = mid;
        }

        if(lo == piles) piles++;
        top[lo] = card;
    }
    // LIS is size of the pile
    cout << piles << endl;
    for (auto ele : top) cout << ele << " ";
    cout << endl;

    // If you want to store elements in piles too.
    vector<vector<int>> pilesVec;  // 2D vector to store subsequences
    for (int i = 0; i < n; i++) {
        int card = nums[i];
        int lo = 0, hi = pilesVec.size();
        
        // Binary search to find the correct pile to place the card
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (pilesVec[mid].back() >= card) hi = mid; // pilesVec[mid][pilesVec[mid].size() - 1]
            else lo = mid + 1;
        }
        
        // If we need to create a new pile
        if (lo == pilesVec.size()) {
            pilesVec.push_back({card});
        } else {
            pilesVec[lo].push_back(card);
        }
    }

    // Print the contents of each pile
    cout << "Number of piles: " << pilesVec.size() << endl;
    for (size_t i = 0; i < pilesVec.size(); i++) {
        cout << "Pile " << i + 1 << ": ";
        for (int card : pilesVec[i]) {
            cout << card << " ";
        }
        cout << endl;
    }

    return 0;
}