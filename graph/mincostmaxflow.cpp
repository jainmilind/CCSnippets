// Warning: when choosing flow_t and cost_t, make sure they can handle the sum of flows and costs, not just individual
// flows and costs.
template<typename flow_t, typename cost_t>
struct min_cost_flow {
    const cost_t COST_INF = numeric_limits<cost_t>::max() / 2;
 
    struct edge {
        int node, rev;
        flow_t capacity;
        cost_t cost;
        int id = -1;
 
        edge() {}
 
        edge(int _node, int _rev, flow_t _capacity, cost_t _cost, int _id = -1)
            : node(_node), rev(_rev), capacity(_capacity), cost(_cost), id(_id) {}
    };
 
    int V = -1, E = 0;
    vector<vector<edge>> adj;
    vector<cost_t> dist;
    vector<int> prev;
    vector<edge*> prev_edge;
    bool too_many_bellman_ford_iterations = false;
 
    min_cost_flow(int vertices = -1) {
        if (vertices >= 0)
            init(vertices);
    }
 
    void init(int vertices) {
        V = vertices;
        E = 0;
        adj.assign(V, {});
        dist.resize(V);
        prev.resize(V);
        prev_edge.resize(V);
        too_many_bellman_ford_iterations = false;
    }
 
    void add_directional_edge(int u, int v, flow_t capacity, cost_t cost, int id = -1) {
        assert(0 <= u && u < V && 0 <= v && v < V);
        edge uv_edge(v, adj[v].size() + (u == v ? 1 : 0), capacity, cost, id);
        edge vu_edge(u, adj[u].size(), 0, -cost);
        adj[u].push_back(uv_edge);
        adj[v].push_back(vu_edge);
        E++;
    }
 
    edge &reverse_edge(const edge &e) {
        return adj[e.node][e.rev];
    }
 
    bool bellman_ford(int source, int sink) {
        for (int i = 0; i < V; i++) {
            dist[i] = COST_INF;
            prev[i] = -1;
            prev_edge[i] = nullptr;
        }
 
        long long work = 0;
        vector<int> last_seen(V, -1);
        vector<int> nodes = {source}, next_nodes;
        dist[source] = 0;
 
        for (int iteration = 0; iteration < V; iteration++) {
            next_nodes.clear();
 
            for (int node : nodes) {
                for (edge &e : adj[node])
                    if (e.capacity > 0 && dist[node] + e.cost < dist[e.node]) {
                        dist[e.node] = dist[node] + e.cost;
                        prev[e.node] = node;
                        prev_edge[e.node] = &e;
 
                        if (last_seen[e.node] != iteration) {
                            last_seen[e.node] = iteration;
                            next_nodes.push_back(e.node);
                        }
                    }
 
                work += adj[node].size();
            }
 
            swap(nodes, next_nodes);
        }
 
        if (work > 1.75 * E * (32 - __builtin_clz(V)) + 100)
            too_many_bellman_ford_iterations = true;
 
        return prev[sink] != -1;
    }
 
    struct dijkstra_state {
        cost_t dist;
        int node;
 
        dijkstra_state() {}
 
        dijkstra_state(cost_t _dist, int _node) : dist(_dist), node(_node) {}
 
        bool operator<(const dijkstra_state &other) const {
            return dist > other.dist;
        }
    };
 
    void dijkstra_check(int node, cost_t potential_dist, int previous, edge *previous_edge,
                        priority_queue<dijkstra_state> &pq) {
        if (potential_dist < dist[node]) {
            dist[node] = potential_dist;
            prev[node] = previous;
            prev_edge[node] = previous_edge;
            pq.emplace(dist[node], node);
        }
    }
 
    bool dijkstra(int source, int sink) {
        dist.assign(V, COST_INF);
        prev.assign(V, -1);
        prev_edge.assign(V, nullptr);
 
        priority_queue<dijkstra_state> pq;
        dijkstra_check(source, 0, -1, nullptr, pq);
 
        while (!pq.empty()) {
            dijkstra_state top = pq.top();
            pq.pop();
 
            if (top.dist > dist[top.node])
                continue;
 
            for (edge &e : adj[top.node])
                if (e.capacity > 0)
                    dijkstra_check(e.node, top.dist + e.cost, top.node, &e, pq);
        }
 
        return prev[sink] != -1;
    }
 
    void reduce_cost() {
        for (int i = 0; i < V; i++)
            for (edge &e : adj[i])
                if (dist[i] < COST_INF && dist[e.node] < COST_INF)
                    e.cost += dist[i] - dist[e.node];
    }
 
    pair<flow_t, cost_t> solve_min_cost_flow(int source, int sink, flow_t flow_goal = numeric_limits<flow_t>::max()) {
        assert(V >= 0);
        flow_t total_flow = 0;
        cost_t total_cost = 0;
 
        while (total_flow < flow_goal && bellman_ford(source, sink)) {
            if (too_many_bellman_ford_iterations)
                break;
 
            // Modification: only continue while achieving negative cost.
            if (dist[sink] >= 0)
                break;
 
            flow_t path_cap = flow_goal - total_flow;
            cost_t cost_sum = 0;
 
            for (int node = sink; prev[node] != -1; node = prev[node])
                path_cap = min(path_cap, prev_edge[node]->capacity);
 
            for (int node = sink; prev[node] != -1; node = prev[node]) {
                edge *e = prev_edge[node];
                e->capacity -= path_cap;
                reverse_edge(*e).capacity += path_cap;
                cost_sum += e->cost;
            }
 
            total_flow += path_cap;
            total_cost += cost_sum * path_cap;
        }
 
        if (too_many_bellman_ford_iterations) {
            cost_t reduce_sum = 0;
 
            do {
                reduce_cost();
                reduce_sum += dist[sink];
 
                // Modification: only continue while achieving negative cost.
                if (reduce_sum >= 0)
                    break;
 
                flow_t path_cap = flow_goal - total_flow;
 
                for (int node = sink; prev[node] != -1; node = prev[node])
                    path_cap = min(path_cap, prev_edge[node]->capacity);
 
                for (int node = sink; prev[node] != -1; node = prev[node]) {
                    edge *e = prev_edge[node];
                    assert(e->cost == 0);
                    e->capacity -= path_cap;
                    reverse_edge(*e).capacity += path_cap;
                }
 
                total_flow += path_cap;
                total_cost += reduce_sum * path_cap;
            } while (total_flow < flow_goal && dijkstra(source, sink));
        }
 
        return make_pair(total_flow, total_cost);
    }
};
