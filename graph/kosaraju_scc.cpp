struct Kosaraju_SCC {
    int n;
    vector<vector<int>> rev, adj_scc;
    vector<bool> vis;
    vector<int> order;
    vector<int> comp;
    // tell which scc the node in original graph belongs to
    vector<int> roots;
    // elements in each comp
    vector<vector<int>> elements;
    // size of scc
    int scc_size = 0;

    Kosaraju_SCC(vector<vector<int>>& adj) : n(adj.size()) {
        vis.resize(n);
        roots.resize(n);
        elements.resize(n);
        rev.resize(n);

        for (int i = 0; i < n; ++i)
            for (int j : adj[i])
                rev[j].push_back(i);
        
        build_scc(adj);
    }

    void dfs1(vector<vector<int>> &adj, int u) {
        vis[u] = 1;
        for (int i : adj[u]) {
            if (vis[i]) continue;
            dfs1(adj, i);
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

    void build_scc(vector<vector<int>> &adj) {
        for (int i = 0; i < n; ++i)
            if (!vis[i])
                dfs1(adj, i);

        fill(begin(vis), end(vis), 0);
        reverse(begin(order), end(order));

        for (int i : order) {
            if (!vis[i]) {
                dfs2(i);

                int cur_root = scc_size++;
                for (int u : comp)
                    roots[u] = cur_root;

                swap(elements[cur_root], comp);
            }
        }

        adj_scc.resize(scc_size);
        for (int v = 0; v < n; ++v) {
            for (int u : adj[v]) {
                int root_v = roots[v], root_u = roots[u];

                if (root_u != root_v)
                    adj_scc[root_v].push_back(root_u);
            }
        }
    }
};
