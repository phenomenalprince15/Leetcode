#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool bfs(vector<vector<int>>& nums, vector<int>& vis, int start) {
    // To detect a cycle using BFS
    vis[start] = 1;
    queue<pair<int, int>> q; // current node and its parent node
    q.push({start, -1}); // push the start node with no parent

    while (!q.empty()) {
        pair<int, int> idx = q.front();
        q.pop();

        for (int node : nums[idx.first]) { // traverse neighbors of the current node
            if (vis[node] == 0) { // if the node hasn't been visited yet
                q.push({node, idx.first});
                vis[node] = 1;
            } else if (node != idx.second) { // if node has been visited and is not the parent
                return true; // cycle detected
            }
        }
    }
    return false; // no cycles found
}

bool dfs(vector<vector<int>>& nums, vector<int>& vis, int start, int parent) {
    vis[start] = 1; // mark the current node as visited
    for (int node : nums[start]) {
        if (vis[node] == 0) { // if the neighbor hasn't been visited yet
            if (dfs(nums, vis, node, start)) { // recursively visit the neighbor
                return true; // cycle found
            }
        } else if (node != parent) { // if the neighbor is visited and not the parent
            return true; // cycle detected
        }
    }
    return false; // no cycle found
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nodes, edges;
    cin >> nodes >> edges; // input number of nodes and edges
    vector<vector<int>> nums(nodes + 1); // adjacency list

    // input edges
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        nums[u].push_back(v); // add undirected edge u-v
        nums[v].push_back(u);
    }

    // output adjacency list
    cout << "Adjacency List:" << endl;
    for (int i = 1; i <= nodes; i++) { // if nodes start from 1, otherwise (0 to nodes)
        cout << "Node " << i << ": ";
        for (int v : nums[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    // visited array for cycle detection
    vector<int> vis(nodes + 1, 0);

    // Using DFS to check for cycles
    if (dfs(nums, vis, 1, -1)) {
        cout << "true" << endl; // cycle detected
    } else {
        cout << "false" << endl; // no cycle detected
    }

    return 0;
}
/*
ip - 1
7 8
1 2
2 5
5 7
7 6
6 3
3 1
3 4
6 4

ip - 2
5 4
1 2
2 3
3 4
4 5

*/