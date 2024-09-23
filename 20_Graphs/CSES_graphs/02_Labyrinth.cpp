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
void bfs(vector<vector<char>>& nums, vector<vector<ll>>& vis, pair<ll, ll>& start, pair<ll, ll>& end) {
    vis[start.first][start.second] = 1;
    queue<pair<ll, ll>> q;
    q.push(start);

    vector<pair<pair<ll, ll>, char>> dirs = {{{-1, 0}, 'U'}, {{0, -1}, 'L'}, {{0, 1}, 'R'}, {{1, 0}, 'D'}};
    vector<vector<int>> prevstep(nums.size(), vector<int>(nums[0].size(), -1));
    
    while (!q.empty()) {
        pair<ll, ll> idx = q.front();
        q.pop();

        if (idx == end) {
            // Reconstruct the path from B to A
            stack<char> path;
            pair<ll, ll> current = end;
            int distance = 0;

            while (current != start) {
                int dirIndex = prevstep[current.first][current.second];
                path.push(dirs[dirIndex].second);
                current.first -= dirs[dirIndex].first.first;
                current.second -= dirs[dirIndex].first.second;
                distance++;
            }

            cout << "YES" << endl;
            cout << distance << endl; // +1 to include the end step

            while (!path.empty()) {
                cout << path.top();
                path.pop();
            }
            cout << endl;
            return;
        }

        for (int i = 0; i < dirs.size(); ++i) {
            ll x = idx.first + dirs[i].first.first;
            ll y = idx.second + dirs[i].first.second;

            if (x >= 0 && x < nums.size() && y >= 0 && y < nums[0].size() &&
                (nums[x][y] == '.' || nums[x][y] == 'B') && vis[x][y] == 0) {
                vis[x][y] = 1;
                q.push({x, y});
                prevstep[x][y] = i; // Store the direction index to reconstruct the path
            }
        }
    }

    cout << "NO" << endl;
}

// void bfs(vector<vector<char>>& nums, vector<vector<ll>>& vis, pair<ll, ll>& start, pair<ll, ll>& end) {
//     vis[start.first][start.second] = 1;
//     queue<pair<pair<ll, ll>, string>> q;
//     q.push({{start.first, start.second}, ""});

//     vector<pair<pair<ll, ll>, char>> dirs = {{{-1, 0}, 'U'}, {{0, -1}, 'L'}, {{0, 1}, 'R'}, {{1, 0}, 'D'}};
//     // vector<char> dirNames = {'U', 'L', 'R', 'D'};
//     while(!q.empty()) {
//         pair<pair<ll, ll>, string> idx = q.front();
//         q.pop();

//         if (idx.first == end) {
//             cout << "YES" << endl;
//             cout << idx.second.length() << endl;
//             cout << idx.second << endl;
//             return;
//         }

//         for (auto& dir : dirs) {
//             ll x = idx.first.first + dir.first.first;
//             ll y = idx.first.second + dir.first.second;
//             // do something with x, y
//             if (x>=0 && x<nums.size() && y>=0 && y<nums[0].size()
//                 && (nums[x][y] == '.' || nums[x][y] == 'B') && vis[x][y] == 0) {

//                     vis[x][y] = 1;
//                     q.push({{x, y}, idx.second + dir.second});
//             }
//         }
//     }

//     cout << "NO" << endl;
//     return;
// }

// start with change
bool dfs(vector<vector<char>>& nums, vector<vector<ll>>& vis, pair<ll, ll> start, pair<ll, ll>& end, string& s) {
    // Base case
    if (start == end) return true;
    vis[start.first][start.second] = 1; // mark visited

    vector<pair<pair<ll, ll>, char>> dirs = {{{-1, 0}, 'U'}, {{0, -1}, 'L'}, {{0, 1}, 'R'}, {{1, 0}, 'D'}};

    for (auto& dir : dirs) {
        ll x = start.first + dir.first.first;
        ll y = start.second + dir.first.second;
        // do something with x, y
        if (x>=0 && x<nums.size() && y>=0 && y<nums[0].size()
            && (nums[x][y] == '.' || nums[x][y] == 'B') && vis[x][y] == 0) {
            s.push_back(dir.second); // add the path
            if (dfs(nums, vis, {x, y}, end, s)) {
                return true; // Path found
            }
            s.pop_back(); // decrease the path, backtrack
        }
    }
    // Unmark the current cell (backtracking)
    vis[start.first][start.second] = 0;
    return false; // No path found
}

// Main function
int main() {
    // Start code here
    ios::sync_with_stdio(false); // Disable synchronization with C I/O for faster I/O
    cin.tie(nullptr); // Untie cin from cout to further improve performance

    ll m , n;
    cin >> m >> n;
    vector<vector<char>> nums(m, vector<char> (n));

    pair<ll, ll> start, end;
    for (ll i=0; i<m; i++) {
        for (ll j=0; j<n; j++) {
            cin >> nums[i][j];
            if (nums[i][j] == 'A') start = {i, j};
            if (nums[i][j] == 'B') end = {i, j};
        }
    }

    vector<vector<ll>> vis(m, vector<ll> (n, 0));
    bfs(nums, vis, start, end);
    // string path;
    // if (dfs(nums, vis, start, end, path)) {
    //     cout << "YES" << endl;
    //     cout << path.length() << endl;
    //     cout << path << endl;
    // } else {
    //     cout << "NO" << endl;
    // }

    return(0);

}