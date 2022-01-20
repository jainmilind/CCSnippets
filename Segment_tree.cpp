struct seg_tree {
    int size;
    typedef int64_t item;
    vector<item> values;
    const item NEUTRAL_ELEMENT = 0;

    inline item merge(item a, item b) {
        return a + b;
    }

    inline item single(int a) {
        return a;
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        values.assign(2 * size, NEUTRAL_ELEMENT);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            values[x] = single(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) set(i, v, 2 * x + 1, lx, m);
        else set(i, v, 2 * x + 2, m, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size())
                values[x] = single(a[lx]);
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r or l >= rx) return NEUTRAL_ELEMENT;
        if (lx >= l and rx <= r) return values[x];
        int m = (lx + rx) / 2;
        item s1 = calc(l, r, 2 * x + 1, lx, m);
        item s2 = calc(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }

    item calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};