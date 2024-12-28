#include <bits/stdc++.h>
using namespace std;

class Kruskal {
public:
    struct Edge {
        int u, v, w;
    };

    int n, m, count = 0;
    vector<Edge> edges, ans;
    int* arr;

    Kruskal() {
        cout << "Enter number of vertices: ";
        cin >> n;
        cout << "Enter number of edges in the graph:";
        cin >> m;

        edges.resize(m);
        cout << "Enter values for u, v, w one by one:\n";
        for (int i = 0; i < m; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        mergeSort(edges);

        arr = (int*)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
    }

    void merge(vector<Edge>& left, vector<Edge>& right, vector<Edge>& result) {
        int i = 0, j = 0, k = 0, p = left.size(), q = right.size();
        while (i < p && j < q) {
            if (left[i].w <= right[j].w) {
                result[k++] = left[i++];
            } else {
                result[k++] = right[j++];
            }
        }
        while (i < p) result[k++] = left[i++];
        while (j < q) result[k++] = right[j++];
    }

    void mergeSort(vector<Edge>& edges) {
        int n = edges.size();
        if (n > 1) {
            vector<Edge> left(edges.begin(), edges.begin() + n / 2);
            vector<Edge> right(edges.begin() + n / 2, edges.end());
            mergeSort(left);
            mergeSort(right);
            merge(left, right, edges);
        }
    }

    void Union(int u, int v) {
        int temp = arr[u];
        for (int i = 0; i < n; i++) {
            if (arr[i] == temp)
                arr[i] = arr[v];
        }
    }

    bool Find(int u, int v) {
        if (arr[u] == arr[v])
        return 1;
        else
            return 0;
    }

    void spanning_tree() {
        int i = 0;
        while (count< n - 1 && i < m) {
            if (Find(edges[i].u, edges[i].v)==0) {
                Union(edges[i].u, edges[i].v);
                ans.push_back(edges[i]);
                count++;
            }
            i++;
        }
    }
};

int main() {
    Kruskal k;
    k.spanning_tree();

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (size_t i = 0; i < k.ans.size(); i++) {
    cout << k.ans[i].u << " " << k.ans[i].v << " " << k.ans[i].w << endl;
}

    return 0;
}
