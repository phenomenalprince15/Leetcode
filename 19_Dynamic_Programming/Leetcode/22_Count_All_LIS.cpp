#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

const long long MOD = 1000000007;

#define ll long long

using namespace std;


// https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/

/*
cnt[i] represents how many subsequences of length dp[i] (LIS ending at index i) can be formed.
The dp[i] stores the length of the LIS ending at i, while cnt[i] tracks the number of such subsequences.

For example:

Consider the array nums = [1, 3, 5, 4, 7].
The LIS length is 4 (subsequences: [1, 3, 5, 7] and [1, 3, 4, 7]).
There are 2 such subsequences.
The cnt[i] values tell how many subsequences of the length dp[i] can end at index i, but the sum of cnt[i] where dp[i] equals the longest length (4 in this case) gives the correct answer.
Example to clarify:
For the input nums = [1, 3, 5, 4, 7]:

dp[] = [1, 2, 3, 3, 4] (the lengths of LIS ending at each index)
cnt[] = [1, 1, 1, 1, 2] (the counts of LIS ending at each index)
The LIS length (maxLis) is 4, but there are 2 such subsequences ([1, 3, 5, 7] and [1, 3, 4, 7]). You need to sum the counts of LIS that have length 4, which in this case are stored in cnt[4] = 2.

If you just return max(cnt), you may incorrectly return 2 when there could be more subsequences to account for. So, you need to sum the counts of subsequences where dp[i] == maxLis.

Hence, the logic of summing up cnt[i] values where dp[i] == maxLis is required.

*/

int main() {

    int n;
    vector<int> nums;
    nums = {1, 2, 4, 3, 5, 4, 7, 2};
    n = nums.size();

    vector<int> dp(n, 1);
    vector<int> cnt(n, 1);
    int maxLis = 1;

    for (int i=1; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (nums[i] > nums[j] && 1+dp[j] > dp[i]) {
                dp[i] = 1+dp[j];
                cnt[i] = cnt[j]; // count reset and storing new LIS
            } else if (nums[i] > nums[j] && 1+dp[j] == dp[i]) {
                cnt[i] += cnt[j]; // store same length LIS previously seen too
            }
        }
        maxLis = max(maxLis, dp[i]); // longest length so far
    }

    int countLIS = 0;
    for (int i=0; i<n; i++) {
        if (dp[i] == maxLis) {
            countLIS += cnt[i];
        }
    }

    cout << countLIS << endl;

    return 0;
}
