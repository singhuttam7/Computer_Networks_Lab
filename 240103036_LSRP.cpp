#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int n;

    cout << "Enter number of routers: ";
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "Enter cost matrix:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    for (int src = 0; src < n; src++)
    {
        vector<int> dist(n, INT_MAX);
        vector<bool> visited(n, false);
        vector<int> parent(n, -1);

        dist[src] = 0;

        for (int k = 0; k < n; k++)
        {
            int u = -1;

            // Find the unvisited router with minimum distance
            for (int i = 0; i < n; i++)
            {
                if (!visited[i] &&
                    (u == -1 || dist[i] < dist[u]))
                {
                    u = i;
                }
            }

            if (u == -1 || dist[u] == INT_MAX)
                break;

            visited[u] = true;

            // Update distances of neighbouring routers
            for (int v = 0; v < n; v++)
            {
                if (!visited[v] &&
                    cost[u][v] != 0 &&
                    dist[u] + cost[u][v] < dist[v])
                {
                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "\nSource Router " << src << ":\n";

        for (int i = 0; i < n; i++)
        {
            cout << "To " << i << " = " << dist[i] << endl;
        }
    }

    return 0;
}
