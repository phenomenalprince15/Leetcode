#include <iostream>
#include <vector>
#include <queue>
#include <stack>


using namespace std;

// Kahn's algorithm
void bfs(vector<int> nums[], queue<pair<int, int>>& q, vector<int>& indegree, vector<int>& ans) {
    // Process each node in the queue
    while (!q.empty()) {
        pair<int, int> idx = q.front();  // Get the current node and its indegree
        q.pop();
        
        ans.push_back(idx.first);  // Add node to the topological order
        
        // Visit all neighbors of the current node
        for (int neighbor : nums[idx.first]) {
            indegree[neighbor]--;  // Reduce indegree of neighbors

            // If the indegree of the neighbor becomes 0, push it to the queue
            if (indegree[neighbor] == 0) {
                q.push({neighbor, indegree[neighbor]});
            }
        }
    }
}

// DFS function for topological sorting
void dfs(vector<int> nums[], vector<int>& vis, stack<int>& st, int i) {
    vis[i] = 1;  // Mark current node as visited

    // Visit all adjacent nodes
    for (auto it : nums[i]) {
        if (!vis[it]) {
            dfs(nums, vis, st, it);
        }
    }

    // Push the current node to the stack after visiting all adjacent nodes
    st.push(i);
}

// Function to return a list containing vertices in topological order.
vector<int> topoSort(int n, vector<int> nums[]) {
    vector<int> vis(n, 0);  // Visited array
    stack<int> st;

    // Perform DFS from each unvisited node
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(nums, vis, st, i);
        }
    }

    // Extract nodes from the stack to form the topological sort order
    // vector<int> ans;
    // while (!st.empty()) {
    //     ans.push_back(st.top());
    //     st.pop();
    // }

    // BFS
    vector<int> indegree(n, 0);

    // Calculate the indegree of each node
    for (int i = 0; i < n; i++) {
        for (int j : nums[i]) {
            indegree[j]++;
        }
    }

    queue<pair<int, int>> q;

    // Initialize the queue with nodes having indegree 0
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push({i, indegree[i]});
        }
    }

    vector<int> ans;
    bfs(nums, q, indegree, ans);  // Perform BFS to get the topological sort

    return ans;
}

// Utility function to print the result
void printTopologicalSort(vector<int> result) {
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    // Example 1: Graph with 6 nodes
    int n1 = 6;
    vector<int> graph1[6];

    graph1[5].push_back(2);
    graph1[5].push_back(0);
    graph1[4].push_back(0);
    graph1[4].push_back(1);
    graph1[2].push_back(3);
    graph1[3].push_back(1);

    cout << "Topological Sort for Example 1: ";
    vector<int> result1 = topoSort(n1, graph1);
    printTopologicalSort(result1);

    // Example 2: Graph with 5 nodes
    int n2 = 5;
    vector<int> graph2[5];

    graph2[0].push_back(1);
    graph2[0].push_back(2);
    graph2[1].push_back(3);
    graph2[2].push_back(3);
    graph2[3].push_back(4);

    cout << "Topological Sort for Example 2: ";
    vector<int> result2 = topoSort(n2, graph2);
    printTopologicalSort(result2);

    // Example 3: Graph with 4 nodes
    int n3 = 4;
    vector<int> graph3[4];

    graph3[1].push_back(0);
    graph3[2].push_back(0);
    graph3[2].push_back(1);
    graph3[3].push_back(2);

    cout << "Topological Sort for Example 3: ";
    vector<int> result3 = topoSort(n3, graph3);
    printTopologicalSort(result3);

    return 0;
}
