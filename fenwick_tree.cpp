template<typename T>
struct fenwick_tree {
    vector<T> BIT;
    int n;
    fenwick_tree(int n = -1) {
        if (n >= 0) init(n);
    }
    void init(int n) {
        BIT.resize(n);
        this->n = n;
    }
    void update(int i, T add) {
        while (i < n) {
            BIT[i] += add;
            i |= (i + 1);
        }
    }
    T sum(int i) {
        T ans{};
        while (i >= 0) {
            ans += BIT[i];
            i = (i & (i + 1)) - 1;
        }
        return ans;
    }
};