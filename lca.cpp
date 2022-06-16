#include "bits/stdc++.h"
using namespace std;

template <typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
public:
    int n;
    vector<vector<T>> mat;
    F func;

    SparseTable(const vector<T>& a, const F& f) : func(f) {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        mat.resize(max_log);
        mat[0] = a;
        for (int j = 1; j < max_log; j++) {
            mat[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T get(int from, int to) const {
        assert(0 <= from && from <= to && to <= n - 1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<int> par(n - 1);
    for (auto& i : par)
        cin >> i;
    vector<vector<int>> adj(n);

    for (int i = 1; i < n; ++i) {
        adj[i].push_back(par[i - 1]);
        adj[par[i - 1]].push_back(i);
    }

    // https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor
    int root = 0;
    vector<int> tour, depth(n), occ(n, -1);

    auto dfs = [&](auto f, int i, int p) -> void {
        if (p != -1)
            depth[i] = depth[p] + 1;

        for (int x : adj[i]) {
            if (x == p) continue;
            tour.push_back(x);
            f(f, x, i);
            tour.push_back(i);
        }
    };

    tour.push_back(root);
    dfs(dfs, root, -1);

    vector<int> lvl(size(tour)), order(size(tour));
    for (int i = 0; i < (int)size(tour); ++i) {
        if (occ[tour[i]] == -1)
            occ[tour[i]] = i;
        lvl[i] = depth[tour[i]];
    }

    iota(begin(order), end(order), 0);
    SparseTable<int> s(order, [&lvl](int i, int j) {return (lvl[i] < lvl[j] ? i : j); });

    while (q--) {
        int u, v;
        cin >> u >> v;
        if (occ[u] > occ[v])
            swap(u, v);
            
        // RMQ on H[u] to H[v] 
        cout << tour[s.get(occ[u], occ[v])] << '\n';
    }
}
