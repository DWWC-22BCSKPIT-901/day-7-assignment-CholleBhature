#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<vector<int>> &heights, vector<vector<bool>> &visited, int x, int y, int prevHeight)
{
    int m = heights.size(), n = heights[0].size();

    // Base conditions
    if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y] || heights[x][y] < prevHeight)
    {
        return;
    }

    visited[x][y] = true;

    // Explore in all 4 directions
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto &dir : directions)
    {
        dfs(heights, visited, x + dir.first, y + dir.second, heights[x][y]);
    }
}

vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
{
    int m = heights.size(), n = heights[0].size();

    // Create visited matrices for both oceans
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));

    // Run DFS for cells adjacent to the Pacific Ocean
    for (int i = 0; i < m; ++i)
    {
        dfs(heights, pacific, i, 0, heights[i][0]);          // Left edge
        dfs(heights, atlantic, i, n - 1, heights[i][n - 1]); // Right edge
    }
    for (int j = 0; j < n; ++j)
    {
        dfs(heights, pacific, 0, j, heights[0][j]);          // Top edge
        dfs(heights, atlantic, m - 1, j, heights[m - 1][j]); // Bottom edge
    }

    // Find all cells that can flow to both oceans
    vector<vector<int>> result;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (pacific[i][j] && atlantic[i][j])
            {
                result.push_back({i, j});
            }
        }
    }

    return result;
}

int main()
{
    vector<vector<int>> heights = {
        {1, 2, 2, 3, 5},
        {3, 2, 3, 4, 4},
        {2, 4, 5, 3, 1},
        {6, 7, 1, 4, 5},
        {5, 1, 1, 2, 4}};

    vector<vector<int>> result = pacificAtlantic(heights);

    cout << "Cells that can flow to both oceans:" << endl;
    for (const auto &cell : result)
    {
        cout << "[" << cell[0] << ", " << cell[1] << "]" << endl;
    }

    return 0;
}
