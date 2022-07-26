struct Kosaraju_SCC {
    int n;
    vector<vector<int>> adj, rev, adj_scc;
    vector<bool> vis;
    vector<int> order;
    vector<int> comp;
    // tell which root the node in original graph belongs to
    vector<int> roots;
    // tells the size of component
    vector<int> comp_size;
    // elements in each comp
    vector<vector<int>> elements;
    // size of scc
    int scc_size = 0;

    Kosaraju_SCC(vector<vector<int>>& adj) : n(adj.size()) {
        vis.resize(n);
        roots.resize(n);
        comp_size.resize(n);
        elements.resize(n);
        rev.resize(n);

        this->adj = adj;
        for (int i = 0; i < n; ++i)
            for (int j : adj[i])
                rev[j].push_back(i);
        calc_scc();
    }

    void dfs1(int u) {
        vis[u] = 1;
        for (int i : adj[u]) {
            if (vis[i]) continue;
            dfs1(i);
        }
        order.push_back(u);
    }

    void dfs2(int u) {
        vis[u] = 1;
        comp.push_back(u);
        for (int i : rev[u]) {
            if (vis[i]) continue;
            dfs2(i);
        }
    }

    void calc_scc() {
        for (int i = 0; i < n; ++i)
            if (!vis[i])
                dfs1(i);

        fill(begin(vis), end(vis), 0);
        reverse(begin(order), end(order));

        for (int i : order) {
            if (!vis[i]) {
                dfs2(i);

                int cur_root = scc_size++;
                for (int u : comp)
                    roots[u] = cur_root;
                comp_size[cur_root] = comp.size();

                swap(elements[cur_root], comp);
            }
        }

        adj_scc.resize(scc_size);
        for (int v = 0; v < n; ++v)
            for (int u : adj[v]) {
                int root_v = roots[v], root_u = roots[u];

                if (root_u != root_v)
                    adj_scc[root_v].push_back(root_u);
            }
    }
};
