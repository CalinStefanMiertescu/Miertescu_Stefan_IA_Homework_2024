#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <tuple>

using namespace std;

int n; 
vector<vector<int>> dist; 

struct State {
    vector<int> path;
    int current_cost;
    int heuristic_cost;
    bool operator>(const State& other) const {
        return (current_cost + heuristic_cost) > (other.current_cost + other.heuristic_cost);
    }
};

int PrimMSTCost(const vector<int>& remaining_cities) {
    if (remaining_cities.empty()) return 0;

    vector<int> key(n, numeric_limits<int>::max());
    vector<bool> inMST(n, false);
    key[remaining_cities[0]] = 0;
    int mst_cost = 0;

    for (int count = 0; count < remaining_cities.size(); ++count) {
        int u = -1;
        for (int i : remaining_cities)
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;

        inMST[u] = true;
        mst_cost += key[u];

        for (int i : remaining_cities)
            if (!inMST[i] && dist[u][i] < key[i])
                key[i] = dist[u][i];
    }

    return mst_cost;
}

int AStarSearch() {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({ {0}, 0, 0 });

    int best_cost = numeric_limits<int>::max();
    vector<int> best_path;

    while (!pq.empty()) {
        State state = pq.top();
        pq.pop();

        if (state.path.size() == n) {
            int total_cost = state.current_cost + dist[state.path.back()][0];
            if (total_cost < best_cost) {
                best_cost = total_cost;
                best_path = state.path;
                best_path.push_back(0);
            }
            continue;
        }

        int last_city = state.path.back();
        vector<int> remaining_cities;
        for (int i = 0; i < n; ++i) {
            if (find(state.path.begin(), state.path.end(), i) == state.path.end())
                remaining_cities.push_back(i);
        }

        int mst_cost = PrimMSTCost(remaining_cities);

        for (int i : remaining_cities) {
            vector<int> new_path = state.path;
            new_path.push_back(i);
            pq.push({ new_path, state.current_cost + dist[last_city][i], mst_cost });
        }
    }

    cout << "Best path: ";
    for (int city : best_path)
        cout << city << " ";
    cout << "\nMinimum cost: " << best_cost << endl;

    return best_cost;
}

int main() {
    cout << "Enter the number of cities: ";
    cin >> n;
    dist.resize(n, vector<int>(n));

    cout << "Enter the distance matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> dist[i][j];

    AStarSearch();

    return 0;
}