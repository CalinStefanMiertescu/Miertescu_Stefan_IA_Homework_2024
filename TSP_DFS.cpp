#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int n; 
vector<vector<int>> dist; 
vector<int> best_path;
int best_cost = numeric_limits<int>::max();

void DFS(vector<int>& path, vector<bool>& visited, int current_cost) {
    if (path.size() == n) {
        current_cost += dist[path.back()][path[0]];
        if (current_cost < best_cost) {
            best_cost = current_cost;
            best_path = path;
            best_path.push_back(path[0]);
        }
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            path.push_back(i);
            DFS(path, visited, current_cost + dist[path[path.size() - 2]][i]);
            visited[i] = false;
            path.pop_back();
        }
    }
}

int main() {
    cout << "Enter the number of cities: ";
    cin >> n;
    dist.resize(n, vector<int>(n));

    cout << "Enter the distance matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> dist[i][j];

    vector<int> path;
    vector<bool> visited(n, false);

    path.push_back(0);
    visited[0] = true;
    DFS(path, visited, 0);

    cout << "Best path: ";
    for (int city : best_path)
        cout << city << " ";
    cout << "\nMinimum cost: " << best_cost << endl;

    return 0;
}