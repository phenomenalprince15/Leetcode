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
https://leetcode.com/problems/number-of-provinces/description/

nums = [[1,1,0],[1,1,0],[0,0,1]]
op - 2

Return the no. of provinces.

Cities are 1, 2, 3, 4, ..... n
Trivially - all have connection to itself and nxn.
So, traverse each city i and bfs on (j), where j = i trivially. nums[i][j] and vis keep track.
*/

// Add functions
void bfs(int node, vector<int>& vis, vector<vector<int>>& nums) {

    queue<int> q;
    q.push(node);
    vis[node] = 1;

    while(!q.empty()) {
        int currNode = q.front();
        q.pop();

        for (int i=0; i<nums.size(); i++) { // traverse all cities
            if(nums[currNode][i] == 1 && !vis[i]) {
                q.push(i);
                vis[i] = 1;
            }
        }
    }

    return;   
}

void dfs(int node, vector<int>& vis, vector<vector<int>>& nums) {
    vis[node] = 1;  // Mark the current city as visited

    for (int i = 0; i < nums.size(); i++) { // traverse all cities
        if (nums[node][i] == 1 && !vis[i]) {
            dfs(i, vis, nums);  // Recursively visit connected cities
        }
    }

    return;
}


// Main function
int main() {
    // Start code here
    int m, n;
    cin >> m >> n;

    vector<vector<int>> nums(n, vector<int> (m));

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cin >> nums[i][j];
        }
    }

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cout << nums[i][j] << " ";
        }
        cout << endl;
    }

    // To find out provinces, Either DFS or BFS
    // Just think about cities
    vector<int> vis(m, 0); // visited cities
    int countPovinces = 0;
    for (int i=0; i<m; i++) {
        if (!vis[i]) {
            countPovinces++;
            // bfs(i, vis, nums);
            dfs(i, vis, nums);
        }
    }

    cout << countPovinces << endl;

    return 0;
}