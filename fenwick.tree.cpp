#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> BIT;
    int n;

public:
    FenwickTree(int size) {
        n = size;
        BIT.resize(n + 1, 0); 
    }

    void update(int idx, int delta) {
        while (idx <= n) {
            BIT[idx] += delta;
            idx += idx & (-idx); 
        }
    }

   
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += BIT[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }

    int rangeQuery(int L, int R) {
        return query(R) - query(L - 1);
    }
};

int main() {
    int n = 10;
    FenwickTree fenwick(n);
    fenwick.update(1, 5); 
    fenwick.update(3, 10); 
    fenwick.update(5, 7); 
  
    cout << "Prefix sum up to index 3: " << fenwick.query(3) << endl;
    cout << "Range sum from index 2 to 5: " << fenwick.rangeQuery(2, 5) << endl;

    return 0;
}
