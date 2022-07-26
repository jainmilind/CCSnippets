const int inf = 4e18;
// returns parents for nodes to get shortest path from s
array<vector<int>, 2> dijkstra(int s, vector<vector<array<int, 2>>>& adj) {
    int n = adj.size();
    vector<int> par(n, -1);

    vector<int> dis(n, inf);
    vector<bool> vis(n);
    dis[s] = 0;
    set<array<int, 2>> q;
    q.insert({ 0, s });

    while (!q.empty()) {
        int u = (*q.begin())[1];
        q.erase(q.begin());

        if (vis[u]) continue;
        vis[u] = 1;

        for (auto [v, w] : adj[u]) {
            if (dis[u] + w < dis[v]) {
                par[v] = u;
                dis[v] = dis[u] + w;
                q.insert({ dis[v], v });
            }
        }
    }

    return { dis, par };
}
