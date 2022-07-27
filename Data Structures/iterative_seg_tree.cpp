template<typename T, typename V = T>
struct seg_tree {
    int n;
    vector<T> tree;

    seg_tree(int n) {
        this->n = n;
        tree.resize(2 * n);
    }

    seg_tree(vector<V>&a) {
        n = a.size();
        tree.resize(2 * n);
        build(a);
    }

    void build(vector<V>& a) {
        for (int i = 0; i < n; i++)
            tree[n + i] = T(a[i]);
        for (int i = n - 1; i > 0; --i)
            tree[i] = T::merge(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int i, T value) {
        tree[i += n] = value;
        for (; i >>= 1; )
            tree[i] = T::merge(tree[i << 1], tree[i << 1 | 1]);
    }

    T query(int l, int r) {
        T resl, resr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = T::merge(resl, tree[l++]);
            if (r & 1)
                resr = T::merge(tree[--r], resr);
        }
        return T::merge(resl, resr);
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
