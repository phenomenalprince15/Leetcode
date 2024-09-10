#include <iostream>
#include <vector>
#include <cmath> // For abs function
#include <algorithm> // For min function
#include <climits>

const long long MOD = 1000000007;

using namespace std;

class DP {
protected:
    vector<int> dp; // DP table for memoization
    
public:
    // Constructor
    DP(int size) : dp(size, -1) {}

    // Reset the DP table
    void reset(int size) {
        dp.assign(size, -1);
    }
};

class DP2D {
    protected:
        vector<vector<int>> dp2D;
        int n, m;

    public:
        // Constructor
        DP2D(int rows, int cols) : dp2D(rows, vector<int>(cols, -1)), n(rows), m(cols) {}

        // Reset the DP table
        void reset(int rows, int cols) {
            dp2D.assign(rows, vector<int>(cols, -1));
            n = rows;
            m = cols;
        }
};

// Problem - https://atcoder.jp/contests/dp/tasks/dp_a
class FrogJump : public DP {
private:
    vector<int> heights; // Heights of the stones

public:
    // Constructor to initialize the heights and DP table
    FrogJump(const vector<int>& h) : DP(h.size()), heights(h) {}

    // Recursive function to find the minimum cost to reach the last stone
    int minCostRecursive(int idx) {
        // Base case
        if (idx <= 0) return 0;
        if (idx == 1) return abs(heights[1] - heights[0]);

        // Recursive
        int left = minCostRecursive(idx - 1) + abs(heights[idx] - heights[idx - 1]);
        int right = minCostRecursive(idx - 2) + abs(heights[idx] - heights[idx - 2]);

        return min(left, right);
    }

    // Recursive function with memoization to find the minimum cost
    int minCostMemoization(int idx) {
        // Base case
        if (idx <= 0) return 0;
        if (idx == 1) return abs(heights[1] - heights[0]);

        // If already computed, return the stored result
        if (dp[idx] != -1) return dp[idx];

        // Recursive
        int left = minCostMemoization(idx - 1) + abs(heights[idx] - heights[idx - 1]);
        int right = minCostMemoization(idx - 2) + abs(heights[idx] - heights[idx - 2]);

        dp[idx] = min(left, right);

        return dp[idx];
    }

    // DP Iteration
    int minCostDPIteration() {
        int minCost = 0;
        // Base case
        dp[0] = 0; // No cost
        if (heights.size() > 1) dp[1] = abs(heights[1] - heights[0]);

        for (int i=2; i<heights.size(); i++) {
            int left = dp[i-1] + abs(heights[i] - heights[i-1]);
            int right = dp[i-2] + abs(heights[i] - heights[i-2]);

            dp[i] = min(left, right);
        }
        minCost = dp[heights.size() - 1];
        return minCost;
    }
};

// Problem - https://atcoder.jp/contests/dp/tasks/dp_b
class FrogJumpK : public DP {
private:
    vector<int> heights; // Heights of the stones
    int k;

public:
    // Constructor to initialize the heights and DP table
    FrogJumpK(const vector<int>& h, int k) : DP(h.size()), heights(h), k(k) {}

    // Recursive function to find the minimum cost to reach the last stone
    int minCostRecursive(int idx) {
        // Base case
        if (idx <= 0) return 0;
        if (idx == 1) return abs(heights[1] - heights[0]);

        int minCost = INT_MAX;

        // Recursive
        for (int i=1; i<=k; i++) {
            if (idx - i >= 0) {
                minCost = min(minCost, minCostMemoization(idx - i) + abs(heights[idx] - heights[idx - i]));
            }
        }

        return minCost;
    }

    // Recursive function with memoization to find the minimum cost
    int minCostMemoization(int idx) {
        // Base case
        if (idx <= 0) return 0;
        if (idx == 1) return abs(heights[1] - heights[0]);

        if (dp[idx] != -1) return dp[idx];
        int minCost = INT_MAX;

        // Recursive
        for (int i=1; i<=k; i++) {
            if (idx - i >= 0) {
                minCost = min(minCost, minCostMemoization(idx - i) + abs(heights[idx] - heights[idx - i]));
            }
        }
        dp[idx] = minCost;
        return dp[idx];
    }

    // DP Iteration
    int minCostDPIteration() {
        // Base Case
        dp[0] = 0;
        dp[1] = abs(heights[1] - heights[0]);

        for (int i=2; i<heights.size(); i++) {
            dp[i] = INT_MAX;
            for (int j=1; j<=k; j++) {
                if (i-j >= 0) {
                    dp[i] = min(dp[i], dp[i - j] + abs(heights[i] - heights[i - j]));
                }
            }
        }

        return dp[heights.size() - 1];
    }
};

// Problem 3 - https://atcoder.jp/contests/dp/tasks/dp_c
class Vacation : public DP2D {
private:
    vector<int> a, b, c;
    int n;

    int maxHappinessRecursive(int day, int lastActivity) {
        // Base case
        if (day >= n) return 0;

        // Conditions
        int happiness = 0;
        if (lastActivity == 0) {
            happiness = max(maxHappinessRecursive(day + 1, 1) + b[day], 
                            maxHappinessRecursive(day + 1, 2) + c[day]);
        } else if (lastActivity == 1) {
            happiness = max(maxHappinessRecursive(day + 1, 0) + a[day], 
                            maxHappinessRecursive(day + 1, 2) + c[day]);
        } else { // lastActivity == 2
            happiness = max(maxHappinessRecursive(day + 1, 0) + a[day], 
                            maxHappinessRecursive(day + 1, 1) + b[day]);
        }
        return happiness;
    }

    int maxHappinessMemoization(int day, int lastActivity) {
        // Base case
        if (day >= n) return 0;

        // If already computed, return the stored result
        if (dp2D[day][lastActivity] != -1) return dp2D[day][lastActivity];

        int maxHappiness = INT_MIN;

        // Conditions
        if (lastActivity != 0) {
            maxHappiness = max(maxHappiness, a[day] + maxHappinessMemoization(day + 1, 0));
        }
        if (lastActivity != 1) {
            maxHappiness = max(maxHappiness, b[day] + maxHappinessMemoization(day + 1, 1));
        }
        if (lastActivity != 2) {
            maxHappiness = max(maxHappiness, c[day] + maxHappinessMemoization(day + 1, 2));
        }

        dp2D[day][lastActivity] = maxHappiness;
        return dp2D[day][lastActivity];
    }

    int maxHappinessDPIteration() {
        // Base case
        dp2D[0][0] = a[0];
        dp2D[0][1] = b[0];
        dp2D[0][2] = c[0];

        // Conditions
        for (int day=1; day < n; day++) {
            // Choose A
            dp2D[day][0] = max(dp2D[day - 1][1] + a[day], dp2D[day - 1][2] + a[day]);
            // Choose B
            dp2D[day][1] = max(dp2D[day - 1][0] + b[day], dp2D[day - 1][2] + b[day]);
            // Choose C
            dp2D[day][2] = max(dp2D[day - 1][0] + c[day], dp2D[day - 1][1] + c[day]);
        }

        return max({dp2D[n-1][0], dp2D[n-1][1], dp2D[n-1][2]});
    }

public:
    Vacation(const vector<int>& a, const vector<int>& b, const vector<int>& c) 
        : DP2D(a.size(), 3), a(a), b(b), c(c), n(a.size()) {}

    // Call this function to get max happiness using recursive approach
    int getMaxHappinessRecursive() {
        return max({maxHappinessRecursive(0, 0), maxHappinessRecursive(0, 1), maxHappinessRecursive(0, 2)});
    }

    // Call this function to get max happiness using memoization
    int getMaxHappinessMemoization() {
        reset(n, m); // Reset the dp table
        return max({maxHappinessMemoization(0, 0), maxHappinessMemoization(0, 1), maxHappinessMemoization(0, 2)});
    }
    int getMaxHappinessDPIteration() {
        reset(n, m);
        return maxHappinessDPIteration();
    }

};

// Problem 4 - https://atcoder.jp/contests/dp/tasks/dp_y
/*
Later ---
*/
class GridII : public DP2D {
    private:
        vector<vector<int>> nums; // Grid with blocked cells marked as 1
    public:
        GridII(vector<vector<int>>& nums, int rows, int cols) : nums(nums), DP2D(rows, cols) {}

        long long gridIIRecursive(int i, int j) {
            // Base case
            if (i < 0 || j < 0) return 0; // Out of bounds
            if (nums[i][j] == 1) return 0; // Blocked cell
            if (i == 0 && j == 0) return 1; // Found 1 path

            long long top = gridIIRecursive(i - 1, j);
            long long left = gridIIRecursive(i, j - 1);

            return (top + left) % MOD; // Apply modulo
        }

        long long gridIIMemoization(int i, int j) {
            // Base case
            if (i < 0 || j < 0) return 0; // Out of bounds
            if (nums[i][j] == 1) return 0; // Blocked cell
            if (i == 0 && j == 0) return 1; // Found 1 path

            if (dp2D[i][j] != -1) return dp2D[i][j];

            long long top = gridIIMemoization(i - 1, j);
            long long left = gridIIMemoization(i, j - 1);
            dp2D[i][j] = (top + left) % MOD; // Apply modulo

            return dp2D[i][j];
        }
};

int main() {
    int n, r, c;
    cin >> r >> c >> n;
    vector<vector<int>> nums(r, vector<int>(c, 0));

    for (int i = 0; i < n; i++) {
        int h, w;
        cin >> h >> w;
        if (h > 0 && h <= r && w > 0 && w <= c) { // Ensure indices are within bounds
            nums[h - 1][w - 1] = 1; // Mark the cell as blocked
        }
    }

    // Optional: print the grid for debugging
    // for (int i = 0; i < r; i++) {
    //     for (int j = 0; j < c; j++) {
    //         cout << nums[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    GridII grid(nums, r, c);
    cout << grid.gridIIMemoization(r - 1, c - 1) << endl; // Output the result

    return 0;
}
