#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> bfs(vector<vector<int>>& nums, vector<int>& indegree) {
        queue<int> q;
        int n = nums.size();
        vector<int> ans;  // Changed to empty initially

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) q.push(i);  // Add nodes with no prerequisites
        }

        while (!q.empty()) {
            int node = q.front();
            ans.push_back(node);  // Append the node to the answer
            q.pop();
            for (auto neighbor : nums[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // If the number of courses in the result is not equal to the total courses, there was a cycle
        if (ans.size() == n) {
            return ans;
        } else {
            return {};  // Return an empty vector if not all courses can be taken
        }
    }

    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
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
    int n1 = 4;
    vector<vector<int>> prerequisites1 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    vector<int> result1 = solution.findOrder(n1, prerequisites1);
    if (!result1.empty()) {
        cout << "Order: ";
        for (int course : result1) {
            cout << course << " ";
        }
        cout << endl;
    } else {
        cout << "Cannot complete all courses" << endl;
    }

    // Test case 2: Courses cannot be completed due to cycle
    int n2 = 2;
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    vector<int> result2 = solution.findOrder(n2, prerequisites2);
    if (!result2.empty()) {
        cout << "Order: ";
        for (int course : result2) {
            cout << course << " ";
        }
        cout << endl;
    } else {
        cout << "Cannot complete all courses" << endl;
    }

    return 0;
}
