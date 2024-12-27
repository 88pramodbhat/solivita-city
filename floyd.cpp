#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

#define INF 1e9 

void floydWarshall(int vertices, vector<vector<int>>& graph) {
   
    vector<vector<int>> dist(vertices, vector<int>(vertices, INF));

   
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (i == j)
                dist[i][j] = 0; 
            else if (graph[i][j] != 0)
                dist[i][j] = graph[i][j];
        }
    }

    // Main Floyd-Warshall algorithm
    for (int k = 0; k < vertices; ++k) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    
    cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (dist[i][j] == INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << dist[i][j];
        }
        cout << endl;
    }
}

int main() {
    cout << "Floyd-Warshall Algorithm\n";

  
    int vertices;
    cout << "Enter the number of vertices: ";
    cin >> vertices;


    vector<vector<int>> graph(vertices, vector<int>(vertices));
    cout << "Enter the adjacency matrix (0 for no edge, weight for edge):\n";
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cin >> graph[i][j];
        }
    }

   
    floydWarshall(vertices, graph);

    return 0;
}
