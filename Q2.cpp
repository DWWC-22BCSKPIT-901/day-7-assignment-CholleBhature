#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
{
    // Edge case: Single node tree
    if (n == 1)
        return {0};

    // Step 1: Build the graph (adjacency list) and degree array
    vector<vector<int>> graph(n);
    vector<int> degree(n, 0);
    for (const auto &edge : edges)
    {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
        degree[edge[0]]++;
        degree[edge[1]]++;
    }

    // Step 2: Initialize the queue with leaf nodes (degree == 1)
    queue<int> leaves;
    for (int i = 0; i < n; i++)
    {
        if (degree[i] == 1)
        {
            leaves.push(i);
        }
    }

    // Step 3: Trim the leaves iteratively
    while (n > 2)
    {
        int leavesCount = leaves.size();
        n -= leavesCount; // Remove current level of leaves

        for (int i = 0; i < leavesCount; i++)
        {
            int leaf = leaves.front();
            leaves.pop();

            // Remove the leaf from its neighbors
            for (int neighbor : graph[leaf])
            {
                degree[neighbor]--;
                if (degree[neighbor] == 1)
                {
                    leaves.push(neighbor);
                }
            }
        }
    }

    // Step 4: Remaining nodes are the roots of MHTs
    vector<int> result;
    while (!leaves.empty())
    {
        result.push_back(leaves.front());
        leaves.pop();
    }

    return result;
}

int main()
{
    // Example usage
    int n = 6;
    vector<vector<int>> edges = {{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}};

    vector<int> mhtRoots = findMinHeightTrees(n, edges);
    cout << "Roots of Minimum Height Trees: ";
    for (int root : mhtRoots)
    {
        cout << root << " ";
    }
    cout << endl;
    return 0;
}
