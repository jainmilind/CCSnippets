typedef int item;
struct sparse {
    vector<int> log;
    vector<vector<item>> table;
    item op(item a, item b) {return min(a, b);} // change this function
    void init(int n, vector<int> &a) {
        log.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i)
            log[i] = log[i / 2] + 1;
        table = vector<vector<item>> (n, vector<item> (log[n] + 1));
        for (int i = 0; i < n; ++i)
            table[i][0] = a[i];
        for (int j = 1; j <= log[n]; ++j)
            for (int i = 0; i + (1ll << j) <= n; ++i)
                table[i][j] = op(table[i][j - 1], table[i + (1ll << (j - 1))][j - 1]);
    }
    sparse(vector<int> &a) {init(a.size(), a);}     // 0-indexed
    item query(int l, int r) {                      // [l, r)
        if (r <= l)
            return 0;
        int j = log[r - l];
        return op(table[l][j], table[r - (1ll << j)][j]);
    }
};