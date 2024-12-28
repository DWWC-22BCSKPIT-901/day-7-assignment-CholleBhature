#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int networkDelayTime(vector<vector<int>> &times, int n, int k)
{
    // Step 1: Build the adjacency list
    vector<vector<pair<int, int>>> graph(n + 1);
    for (const auto &time : times)
    {
        int u = time[0], v = time[1], w = time[2];
        graph[u].emplace_back(v, w);
    }

    // Step 2: Min-heap to perform Dijkstra's algorithm
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;
    pq.emplace(0, k); // {distance, node}

    while (!pq.empty())
    {
        int curDist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        // If the current distance is greater than the stored distance, skip
        if (curDist > dist[node])
            continue;

        // Relax all edges
        for (const auto &edge : graph[node])
        {
            int neighbor = edge.first;
            int weight = edge.second;

            if (dist[node] + weight < dist[neighbor])
            {
                dist[neighbor] = dist[node] + weight;
                pq.emplace(dist[neighbor], neighbor);
            }
        }
    }

    // Step 3: Calculate the maximum time
    int maxTime = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (dist[i] == INT_MAX)
            return -1; // Node not reachable
        maxTime = max(maxTime, dist[i]);
    }

    return maxTime;
}

int main()
{
    vector<vector<int>> times = {
        {2, 1, 1},
        {2, 3, 1},
        {3, 4, 1}};
    int n = 4, k = 2;

    int result = networkDelayTime(times, n, k);
    cout << "Minimum time for all nodes to receive the signal: " << result << endl;

    return 0;
}
