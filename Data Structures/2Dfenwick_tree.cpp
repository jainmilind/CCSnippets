template<class T>
struct fenwick_tree2D {
    vector<vector<T>> bit;
    int n;
 
    fenwick_tree2D(int N) {
        n = N;
        bit.assign(n, vector<T>(n));
    }
 
    T sum(int x, int y) {
        T res = 0;
        for (; x >= 0; x = (x & (x + 1)) - 1)
            for (int y1 = y; y1 >= 0; y1 = (y1 & (y1 + 1)) - 1)
                res += bit[x][y1];
        return res;
    }
 
    T sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
    }
 
    void add(int x, int y, T delta) {
        for (; x < n; x = x | (x + 1))
            for (int y1 = y; y1 < n; y1 = y1 | (y1 + 1))
                bit[x][y1] += delta;
    }
};
 