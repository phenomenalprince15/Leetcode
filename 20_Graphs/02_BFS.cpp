#include <iostream>
#include <vector>
#include <queue>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

vector<int> bfsOfGraph(int n, vector<vector<int>>& adj) { // vector<int> adj[]
    vector<int> vis(n, 0);   // Visited array
    vis[0] = 1;              // Mark node 0 as visited
    vector<int> bfs;         // Resultant BFS order

    queue<int> q;
    q.push(0);               // Start BFS from node 0

    // until queue is empty, traverse and mark visited
    while (!q.empty()) {
        int frontNode = q.front(); // take first node
        q.pop();                   // pop out front node
        bfs.push_back(frontNode);   // push it in result

        for (auto it : adj[frontNode]) { // traverse adjacent nodes
            if (!vis[it]) {              // check if node is visited
                vis[it] = 1;
                q.push(it);             // add to queue if not visited
            }
        }
    }
    return bfs;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int nodes, edges;
        cin >> nodes >> edges;

        //vector<int> adj[nodes];
        vector<vector<int>> adj(nodes);

        for (int i = 0; i < edges; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            // adj[v].push_back(u); // Uncomment for undirected graph
        }

        vector<int> ans = bfsOfGraph(nodes, adj);
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
