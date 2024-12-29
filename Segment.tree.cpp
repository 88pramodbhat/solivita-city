#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
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

    void update(int idx, int value, int node, int start, int end) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;

            if (start <= idx && idx <= mid) {
                update(idx, value, left_child, start, mid);
            } else {
                update(idx, value, right_child, mid + 1, end);
            }
              tree[node] = tree[left_child] + tree[right_child];
        }
    }

    int query(int L, int R, int node, int start, int end) {
        if (R < start || L > end) {
            return 0;
        }
        if (L <= start && end <= R) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        int left_sum = query(L, R, left_child, start, mid);
        int right_sum = query(L, R, right_child, mid + 1, end);

        return left_sum + right_sum;
    }

public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n, 0);
        build(data, 0, 0, n - 1);
    }

    void update(int idx, int value) {
        update(idx, value, 0, 0, n - 1);
    }

    int query(int L, int R) {
        return query(L, R, 0, 0, n - 1);
    }
};

int main() {
    vector<int> data = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(data);
    cout << "Sum of range [1, 4]: " << segTree.query(1, 4) << endl;
    segTree.update(3, 10);
    cout << "After update, sum of range [1, 4]: " << segTree.query(1, 4) << endl;

    return 0;
}
