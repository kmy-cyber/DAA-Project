#pragma once
#include "../utils/types.hpp"
#include "../utils/edge.hpp"

struct SpanningTree {
    vEdges edges;
    vi degree;
    int n;

    SpanningTree(int n) : n(n), degree(n, 0) {}

    void addEdge(const Edge& e) {
        edges.push_back(e);
        degree[e.u]++;
        degree[e.v]++;
    }

    void removeEdge(int u, int v) {
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if ((it->u == u && it->v == v) || (it->u == v && it->v == u)) {
                degree[it->u]--;
                degree[it->v]--;
                edges.erase(it);
                return;
            }
        }
    }

    ll cost() const {
        ll total = 0;
        for (const auto& e : edges) {
            total += e.w;
        }
        return total;
    }

    bool isFeasible(const vi& deg_limit) const {
        if ((int)edges.size() != n - 1) return false;
        for (int i = 0; i < n; i++) {
            if (degree[i] > deg_limit[i]) return false;
        }
        return true;
    }
};



/* ========================================
   MST clásico (Kruskal)
   ======================================== */
SpanningTree classicMST(const Graph& G, const std::vector<double>& costs) {
    SpanningTree tree(G.n);
    
    std::vector<std::pair<double, int>> sorted_edges;
    for (int i = 0; i < (int)G.edges.size(); i++) {
        sorted_edges.push_back({costs[i], i});
    }
    std::sort(sorted_edges.begin(), sorted_edges.end());

    DSU dsu(G.n);

    for (const auto& p : sorted_edges) {
        int idx = p.second;
        const Edge& e = G.edges[idx];

        if (dsu.find(e.u) != dsu.find(e.v)) {
            tree.addEdge(e);
            dsu.merge(e.u, e.v);
            
            if ((int)tree.edges.size() == G.n - 1) {
                break;
            }
        }
    }

    return tree;
}



SpanningTree simpleGreedy(const Graph& G, const std::vector<double>* custom_costs = nullptr) {
    SpanningTree tree(G.n);
    
    std::vector<std::pair<double, int>> sorted_edges;
    for (int i = 0; i < (int)G.edges.size(); i++) {
        double cost = custom_costs ? (*custom_costs)[i] : G.edges[i].w;
        sorted_edges.push_back({cost, i});
    }
    std::sort(sorted_edges.begin(), sorted_edges.end());

    DSU dsu(G.n);
    vi deg(G.n, 0);

    for (const auto& p : sorted_edges) {
        int idx = p.second;
        const Edge& e = G.edges[idx];

        if (dsu.find(e.u) == dsu.find(e.v)) continue;
        if (deg[e.u] >= G.b[e.u]) continue;
        if (deg[e.v] >= G.b[e.v]) continue;

        tree.addEdge(e);
        deg[e.u]++;
        deg[e.v]++;
        dsu.merge(e.u, e.v);

        if ((int)tree.edges.size() == G.n - 1) {
            break;
        }
    }

    return tree;
}