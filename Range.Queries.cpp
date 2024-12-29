#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree, lazy;
    int n;

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;
            build(data, left_child, start, mid);
            build(data, right_child, mid + 1, end);
            tree[node] = tree[left_child] + tree[right_child];
        }
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];

            if (start != end) {
                int left_child = 2 * node + 1;
                int right_child = 2 * node + 2;
                lazy[left_child] += lazy[node];
                lazy[right_child] += lazy[node];
            }
             lazy[node] = 0;
        }
    }

    void updateRange(int L, int R, int value, int node, int start, int end) {
        propagate(node, start, end);

        if (R < start || L > end) {
            return;
        }

        if (L <= start && end <= R) {
            tree[node] += (end - start + 1) * value;

            if (start != end) {
                int left_child = 2 * node + 1;
                int right_child = 2 * node + 2;
                lazy[left_child] += value;
                lazy[right_child] += value;
            }
            return;
        }

        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        updateRange(L, R, value, left_child, start, mid);
        updateRange(L, R, value, right_child, mid + 1, end);
        tree[node] = tree[left_child] + tree[right_child];
    }

    int queryRange(int L, int R, int node, int start, int end) {
        propagate(node, start, end);

        if (R < start || L > end) {
            return 0;
        }

        if (L <= start && end <= R) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        int left_sum = queryRange(L, R, left_child, start, mid);
        int right_sum = queryRange(L, R, right_child, mid + 1, end);

        return left_sum + right_sum;
    }

public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(data, 0, 0, n - 1);
    }

    void updateRange(int L, int R, int value) {
        updateRange(L, R, value, 0, 0, n - 1);
    }

    int queryRange(int L, int R) {
        return queryRange(L, R, 0, 0, n - 1);
    }
};

int main() {
    vector<int> data = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(data);

    cout << "Sum of range [1, 4]: " << segTree.queryRange(1, 4) << endl;

    segTree.updateRange(1, 3, 10);
    cout << "After range update, sum of range [1, 4]: " << segTree.queryRange(1, 4) << endl;

    cout << "Sum of range [0, 5]: " << segTree.queryRange(0, 5) << endl;

    return 0;
}
