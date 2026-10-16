#include <iostream>
#include <vector>
using namespace std;

const int INF = 9999;

struct Node
{
    char name;
    vector<int> dist;
    vector<int> nextHop;
};

int main()
{
    int n = 5;
    char names[] = {'A', 'B', 'C', 'D', 'E'};

    int cost[5][5] =
    {
        {0, 2, 5, INF, INF},
        {2, 0, INF, 3, INF},
        {5, INF, 0, 1, 7},
        {INF, 3, 1, 0, 6},
        {INF, INF, 7, 6, 0}
    };

    vector<Node> nodes(n);

    for (int i = 0; i < n; i++)
    {
        nodes[i].name = names[i];

        for (int j = 0; j < n; j++)
        {
            nodes[i].dist.push_back(cost[i][j]);

            if (i == j)
                nodes[i].nextHop.push_back(i);
            else if (cost[i][j] != INF)
                nodes[i].nextHop.push_back(j);
            else
                nodes[i].nextHop.push_back(-1);
        }
    }

    cout << "===== INITIAL ROUTING TABLE =====\n";

    for (int i = 0; i < n; i++)
    {
        cout << "\nRouter " << names[i] << ":\n";

        for (int j = 0; j < n; j++)
        {
            cout << "Destination: " << names[j]
                 << "  Distance: ";

            if (nodes[i].dist[j] == INF)
                cout << "INF";
            else
                cout << nodes[i].dist[j];

            cout << "  Next Hop: ";

            if (nodes[i].nextHop[j] == -1)
                cout << "-";
            else
                cout << names[nodes[i].nextHop[j]];

            cout << endl;
        }
    }

    bool updated;

    do
    {
        updated = false;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (cost[i][j] == INF || i == j)
                    continue;

                for (int k = 0; k < n; k++)
                {
                    if (nodes[j].dist[k] == INF)
                        continue;

                    int newDistance =
                        cost[i][j] + nodes[j].dist[k];

                    if (newDistance < nodes[i].dist[k])
                    {
                        nodes[i].dist[k] = newDistance;
                        nodes[i].nextHop[k] = j;
                        updated = true;
                    }
                }
            }
        }

    } while (updated);

    cout << "\n\n===== UPDATED ROUTING TABLE =====\n";

    for (int i = 0; i < n; i++)
    {
        cout << "\nRouter " << names[i] << ":\n";

        for (int j = 0; j < n; j++)
        {
            cout << "Destination: " << names[j]
                 << "  Distance: ";

            if (nodes[i].dist[j] == INF)
                cout << "INF";
            else
                cout << nodes[i].dist[j];

            cout << "  Next Hop: ";

            if (nodes[i].nextHop[j] == -1)
                cout << "-";
            else
                cout << names[nodes[i].nextHop[j]];

            cout << endl;
        }
    }

    return 0;
}
