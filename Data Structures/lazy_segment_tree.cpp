template<typename T>
struct seg_tree {
    int size, n;
    vector<T> values, lazy;
    T lazy_neutral = 0;
    T neutral = 0;

    T merge(T a, T b) {
        return a + b;
    }

    T upd(T a, T b) {
        return a + b;
    }

    void push(int x, int lx, int rx) {
        if (lazy[x] == lazy_neutral) return;

        values[x] = upd(values[x], (rx - lx) * lazy[x]);

        if (rx - lx != 1) {
            lazy[2 * x + 1] = upd(lazy[2 * x + 1], lazy[x]);
            lazy[2 * x + 2] = upd(lazy[2 * x + 2], lazy[x]);
        }
        lazy[x] = lazy_neutral;
    }

    seg_tree(vector<int>&a) : n(a.size()) {
        size = 1;
        while (size < n) size *= 2;
        values.resize(2 * size, neutral);
        lazy.resize(2 * size, lazy_neutral);
        build(a);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < n)
                values[x] = a[lx];
            return;
        }

        int m = (lx + rx) >> 1;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }

    void update(int l, int r, T& v, int x, int lx, int rx) {
        push(x, lx, rx);
        if (lx >= r or l >= rx) return;
        if (lx >= l and rx <= r) {
            lazy[x] = upd(lazy[x], v);
            push(x, lx, rx);
            return;
        }

        int m = (lx + rx) >> 1;
        update(l, r, v, 2 * x + 1, lx, m);
        update(l, r, v, 2 * x + 2, m, rx);

        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void update(int l, int r, T v) {
        update(l, r, v, 0, 0, size);
    }

    T query(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if (lx >= r or l >= rx) return neutral;
        if (lx >= l and rx <= r)
            return values[x];

        int m = (lx + rx) >> 1;
        T s1 = query(l, r, 2 * x + 1, lx, m);
        T s2 = query(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};
