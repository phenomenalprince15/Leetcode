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


// Add functions
void bfs(vector<vector<int>>& nums, vector<int>& vis, int i, vector<int>& ans) {
    vis[i] = 1;
    queue<int> q;
    q.push(i);

    // vector<pair<int, int>> dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    while(!q.empty()) {
        int idx = q.front();
        q.pop();
        ans.push_back(idx);

        for (int it : nums[idx]) {
            if (!vis[it]) {
                vis[it] = 1;
                q.push(it);
            }
        }
        // if (q.empty()) {
        //     ans.push_back(it);
        // }
    }
    return;
}

// Main function
int main() {
    ios::sync_with_stdio(false); // Disable synchronization with C I/O for faster I/O
    cin.tie(nullptr); // Untie cin from cout to further improve performance
    // Start code here
    int nodes , edges;
    cin >> nodes >> edges;

    vector<vector<int>> nums(nodes + 1);  
    
    for (int i=0; i<edges; i++) {
        int u, v;
        cin >> u >> v;
        nums[u].push_back(v); // add undirected edge u-v
        nums[v].push_back(u);
    }
    // output adjacency list
    // cout << "Adjacency List:" << endl;
    // for (int i = 1; i <= nodes; i++) { // if nodes start from 1, otherwise (0 to nodes)
    //     cout << "Node " << i << ": ";
    //     for (int v : nums[i]) {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }

    vector<int> vis(nodes + 1, 0);
    int comp = 0;
    vector<vector<int>> components;
    for (int i=1; i<=nodes; i++) {
        if (!vis[i]) {
            comp++;
            vector<int> ans;
            bfs(nums, vis, i, ans);
            components.push_back(ans);
        }
    }
    cout << comp - 1 << endl; // minimum roads req. = no. of components - 1
    // for (const auto& component : components) {
    //     for (int node : component) {
    //         cout << node << " ";
    //     }
    //     cout << endl; // Print nodes in each component
    // }

    for (int i=1; i<components.size(); i++) {
         cout << components[i-1][0] << " " << components[i][0] << endl;
    }
    
    return(0);

}
/*
Input:

4 2
1 2
3 4
Output:

1
2 3

ip
10 10
2 5
5 6
1 4
6 8
2 6
3 6
1 10
8 9
2 3
5 8

op
2
1 2
2 7
*/