vector<int> topo_sort(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> ans, deg(n);

    for (int i = 0; i < n; ++i)
        for (int j : adj[i])
            deg[j]++;

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (deg[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        ans.push_back(u);

        for (int i : adj[u]) {
            deg[i]--;
            if (deg[i] == 0)
                q.push(i);
        }
    }

    return ans;
}
