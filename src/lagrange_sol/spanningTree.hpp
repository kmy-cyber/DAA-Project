#pragma once
#include "../utils/types.hpp"
#include "../utils/edge.hpp"

/* ========================================
   Estructura para el árbol generador
   ======================================== */
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
