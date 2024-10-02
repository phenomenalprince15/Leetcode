#include <iostream>
#include <vector>
#include <queue>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<int>& vis, vector<int>& dfsList) {
    vis[node] = 1; // mark node as visited while recursing back

    dfsList.push_back(node); // add in list as it's been traversed

    for (auto it : adj[node]) { // traverse all connected neighbors/nodes if not visited
        if (!vis[it]) {
            dfs(it, adj, vis, dfsList);
        }
    }
}

vector<int> dfsOfGraph(int n, vector<vector<int>>& adj) { // vector<int> adj[]
    vector<int> dfsList;
    vector<int> vis(n, 0);
    dfs(0, adj, vis, dfsList);

    return dfsList;
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

        vector<int> ans = dfsOfGraph(nodes, adj);
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
