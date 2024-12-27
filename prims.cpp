#include <iostream>
#include <climits>
#include <queue>

using namespace std;

class Graph {
    int V;
    int** adjMatrix;

public:
    Graph(int V) {
        this->V = V;
        adjMatrix = new int*[V];
        for (int i = 0; i < V; i++) {
            adjMatrix[i] = new int[V];
            for (int j = 0; j < V; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; 
    }

    void primMST() {
        int* parent = new int[V];
        int* key = new int[V];
        bool* inMST = new bool[V];

        for (int i = 0; i < V; i++) {
            key[i] = INT_MAX;
            inMST[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < V - 1; count++) {
            int minKey = INT_MAX, u;
            for (int v = 0; v < V; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

         
            inMST[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " \t" << adjMatrix[i][parent[i]] << endl;
        }

        delete[] parent;
        delete[] key;
        delete[] inMST;
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
};

int main() {
    int V = 5; 
    Graph g(V);

    g.addEdge(0, 1, 2);
  
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
  
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
  
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.primMST();

    return 0;
}
