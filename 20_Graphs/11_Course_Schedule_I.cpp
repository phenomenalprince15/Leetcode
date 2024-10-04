#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool bfs(vector<vector<int>>& nums, vector<int>& indegree) {
        queue<int> q;
        for (int i = 0; i < nums.size(); i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> ans;
        while (!q.empty()) {
            int node = q.front();
            ans.push_back(node);
            q.pop();
            for (auto neighbor : nums[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return (ans.size() == nums.size());
    }

    bool canFinish(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> nums(n);
        for (auto x : prerequisites) {
            nums[x[1]].push_back(x[0]);
        }

        vector<int> indegree(n, 0);
        for (int i = 0; i < n; i++) {
            for (auto j : nums[i]) {
                indegree[j]++;
            }
        }
        return bfs(nums, indegree);
    }
};

int main() {
    Solution solution;

    // Test case 1: Courses can be completed
    int n1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    cout << "Test case 1: " << (solution.canFinish(n1, prerequisites1) ? "Can finish" : "Cannot finish") << endl;

    // Test case 2: Courses cannot be completed due to cycle
    int n2 = 2;
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    cout << "Test case 2: " << (solution.canFinish(n2, prerequisites2) ? "Can finish" : "Cannot finish") << endl;

    // Test case 3: No prerequisites, all courses can be completed
    int n3 = 3;
    vector<vector<int>> prerequisites3 = {};
    cout << "Test case 3: " << (solution.canFinish(n3, prerequisites3) ? "Can finish" : "Cannot finish") << endl;

    // Test case 4: More complex case, courses can be completed
    int n4 = 4;
    vector<vector<int>> prerequisites4 = {{1, 0}, {2, 1}, {3, 2}};
    cout << "Test case 4: " << (solution.canFinish(n4, prerequisites4) ? "Can finish" : "Cannot finish") << endl;

    return 0;
}
