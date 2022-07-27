template<typename T, typename V = T>
struct seg_tree {
    int size, n;
    vector<T> values;

    seg_tree(vector<V> &a) : n(a.size()) {
        size = 1;
        while (size < n) size *= 2;
        values.resize(2 * size);
        build(a);
    }

    seg_tree(int N) : n(N) {
        size = 1;
        while (size < n) size *= 2;
        values.resize(2 * size);
    }

    void update(int i, T& v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            values[x] = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i < m) update(i, v, 2 * x + 1, lx, m);
        else update(i, v, 2 * x + 2, m, rx);
        values[x] = T::merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void update(int i, T v) {
        update(i, v, 0, 0, size);
    }

    void build(vector<V> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < n)
                values[x] = a[lx];
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = T::merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<V> &a) {
        build(a, 0, 0, size);
    }

    T query(int l, int r, int x, int lx, int rx) {
        if (lx >= r or l >= rx) return T();
        if (lx >= l and rx <= r) return values[x];
        int m = (lx + rx) >> 1;
        T s1 = query(l, r, 2 * x + 1, lx, m);
        T s2 = query(l, r, 2 * x + 2, m, rx);
        return T::merge(s1, s2);
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};

struct item {
    int val;
    item(): val(0) {}
    item(int x): val(x) {}
    static item merge(item& x, item&y) {
        return item(max(x.val, y.val));
    }
};
