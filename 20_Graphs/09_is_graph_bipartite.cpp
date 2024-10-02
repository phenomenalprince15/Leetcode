#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool bfs(vector<vector<int>>& nums, vector<int>& vis, int start) {
        queue<pair<int, int>> q;
        q.push({start, 0}); // Start with color 0
        vis[start] = 0; // Mark start as colored with 0

        while (!q.empty()) {
            pair<int, int> idx = q.front();
            q.pop();

            for (int node : nums[idx.first]) { // node is neighbor
                if (vis[node] == -1) { // If not visited
                    if (idx.second == 0) {
                        q.push({node, 1}); // Color with 1
                        vis[node] = 1; // Mark as visited
                    } else {
                        q.push({node, 0}); // Color with 0
                        vis[node] = 0; // Mark as visited
                    }
                } else if (idx.second == vis[node]) {
                    return false; // Not bipartite
                }
            }
        }
        return true; // Component is bipartite
    }

    bool isBipartite(vector<vector<int>>& nums) {
        int n = nums.size();
        vector<int> vis(n, -1); // Initialize visitation status

        for (int i = 0; i < n; i++) {
            if (vis[i] == -1) { // If unvisited, perform BFS
                if (!bfs(nums, vis, i)) {
                    return false; // If any component is not bipartite
                }
            }
        }
        return true; // All components are bipartite
    }
};

int main() {
    Solution solution;
    int nodes, edges;

    // Example 1
    cout << "Example 1: \n";
    nodes = 4;
    edges = 5;
    vector<vector<int>> graph1(nodes);
    graph1[0] = {1, 2, 3};
    graph1[1] = {0, 2};
    graph1[2] = {0, 1, 3};
    graph1[3] = {0, 2};

    cout << "Is the graph bipartite? " << (solution.isBipartite(graph1) ? "TRUE" : "FALSE") << endl;

    // Example 2
    cout << "Example 2: \n";
    nodes = 5;
    edges = 6;
    vector<vector<int>> graph2(5);
    graph2[0] = {1};
    graph2[1] = {0, 3};
    graph2[2] = {3, 4};
    graph2[3] = {1, 2};
    graph2[4] = {2};

    cout << "Is the graph bipartite? " << (solution.isBipartite(graph2) ? "TRUE" : "FALSE") << endl;

    // Example 3
    cout << "Example 3: \n";
    nodes = 3;
    edges = 3;
    vector<vector<int>> graph3(3);
    graph3[0] = {1, 2};
    graph3[1] = {0, 2};
    graph3[2] = {0, 1};

    cout << "Is the graph bipartite? " << (solution.isBipartite(graph3) ? "TRUE" : "FALSE") << endl;

    return 0;
}
