#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

const long long MOD = 1000000007;

#define ll long long

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // Initialize the adjacency matrix with 0
    int adj[n+1][n+1] = {0}; // Correct size is (n+1) x (n+1)

    // Input the edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;  // Mark the edge from u to v
        adj[v][u] = 1;  // Since it's an undirected graph, mark v to u as well
    }

    // Print the adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Inputs for List :: " << endl;
    // List
    vector<vector<int>> graph(n+1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Since it's an undirected graph
    }

    // Print the adjacency list
    cout << "Adjacency List:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Vertex/Node " << i << ": ";
        for (int v : graph[i]) {
            cout << v << " ";
        }
        cout << endl;
    }


    cout << "Inputs for List with weights :: " << endl;
    // Store in pairs, for weights given
    vector<vector<pair<int, ll>>> graphW(n+1); // Pair of vertex and weight

    // Input the edges with weights for the adjacency list
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w; // Weight
        cin >> u >> v >> w;
        graphW[u].push_back({v, w});
        graphW[v].push_back({u, w}); // Since it's an undirected graph
    }

    // Print the adjacency list
    cout << "Adjacency List:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Vertex/Node " << i << ": ";
        for (const auto& edge : graphW[i]) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }

    return 0;
}
/*
if weights are given then, use weights instead of 1 in list or matrix.

Input :
5 4

1 2
2 3
3 4
4 5

Output :
$ ./a.exe 
5 4
1 2
2 3
3 4
4 5
Adjacency Matrix:
0 1 0 0 0
1 0 1 0 0
0 1 0 1 0 
0 0 1 0 1
0 0 0 1 0
1 2
2 3
3 4
4 5
Adjacency List:
Vertex/Node 1: 2
Vertex/Node 2: 1 3
Vertex/Node 3: 2 4 
Vertex/Node 4: 3 5
Vertex/Node 5: 4
1 2 3
2 3 4
3 4 5
4 5 6
Adjacency List:
Vertex/Node 1: (2, 3)
Vertex/Node 2: (1, 3) (3, 4) 
Vertex/Node 3: (2, 4) (4, 5)
Vertex/Node 4: (3, 5) (5, 6)
Vertex/Node 5: (4, 6)
*/