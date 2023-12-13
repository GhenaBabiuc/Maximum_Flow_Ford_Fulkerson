#include <iostream>
#include <climits>
#include <queue>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

#define V 20

bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        vector<int> path;
        int path_flow = INT_MAX;

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
            path.push_back(v);
        }
        path.push_back(s);

        cout << "Calea de crestere gasita: ";
        for (int i = path.size() - 1; i > 0; --i) {
            cout << path[i] << " -> ";
        }
        cout << path[0] << " cu fluxul: " << path_flow << endl;

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int graph[V][V] = {0};
    int m, n;
    ifstream fin("../flux.in");
    fin >> n >> m;

    int a, b, cap;
    for (int i = 0; i < m; i++) {
        fin >> a >> b >> cap;
        graph[a - 1][b - 1] = cap;
    }
    fin.close();

    int s = 0;
    int t = n - 1;
    cout << "Calcularea fluxului maxim..." << endl;
    cout << "Fluxul maxim: \n" << fordFulkerson(graph, s, t) << endl;

    return 0;
}
