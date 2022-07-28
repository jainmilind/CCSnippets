struct Tarjan_SCC {
    int n;
    vector<bool> on_stack;
    // low link values for each node
    vector<int> low;
    // ids for each node for dfs
    vector<int> ids;
    // tell which scc does each node belong to
    vector<int> roots;
    // scc graph
    vector<vector<int>> adj_scc;
    // elements in each comp
    vector<vector<int>> elements;
    // dfs stack
    stack<int> s;
    int timer, scc_size;

    Tarjan_SCC(vector<vector<int>>& adj) : n(adj.size()) {
        on_stack.resize(n);
        low.resize(n);
        ids.resize(n);
        roots.resize(n);
        elements.resize(n);
        timer = scc_size = 0;

        for (int i = 0; i < n; ++i)
            if (!ids[i])
                dfs(adj, i);

        build_scc(adj);
    };

    void dfs(vector<vector<int>>& adj, int u) {
        s.push(u);
        low[u] = ids[u] = ++timer;
        on_stack[u] = 1;

        for (int i : adj[u]) {
            if (!ids[i])
                dfs(adj, i);
            if (on_stack[i])
                low[u] = min(low[u], low[i]);
        }

        if (ids[u] == low[u]) {
            int v = -1;
            while (v != u) {
                v = s.top();
                s.pop();
                elements[scc_size].push_back(v);
                on_stack[v] = 0;
                roots[v] = scc_size;
            }
            scc_size++;
        }
    }

    void build_scc(vector<vector<int>>& adj) {
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
