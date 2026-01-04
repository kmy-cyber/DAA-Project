
#pragma once
#include "spanningTree.hpp"
#include "../utils/graph.hpp"
#include "../utils/dsu.hpp"


struct KruskalResult {
    SpanningTree tree;
    int last_edge_index;
    bool success;

    KruskalResult(int n) : tree(n), last_edge_index(-1), success(false) {}
};


int treeDegree(const std::vector<int>& component, const vi& tree_deg) {
    int delta = 0;
    for (int v : component) {
        delta += tree_deg[v];
    }
    return delta;
}

int treeCapacity(const std::vector<int>& component, const vi& deg_limit) {
    int cap = 0;
    for (int v : component) {
        cap += deg_limit[v];
    }
    return cap;
}


/* ========================================
   KRUSKALX: Construcción con look-ahead
   ======================================== */


KruskalResult kruskalX(const Graph& G, const std::vector<double>& costs) {
    KruskalResult result(G.n);
    
    // Crear lista de aristas ordenadas por costo
    std::vector<std::pair<double, int>> sorted_edges;
    for (int i = 0; i < (int)G.edges.size(); i++) {
        sorted_edges.push_back({costs[i], i});
    }
    std::sort(sorted_edges.begin(), sorted_edges.end());

    DSU dsu(G.n);
    vi deg(G.n, 0);

    for (int k = 0; k < (int)sorted_edges.size(); k++) {
        int idx = sorted_edges[k].second;
        const Edge& e = G.edges[idx];

        // Verificar restricciones de grado
        if (deg[e.u] >= G.b[e.u] || deg[e.v] >= G.b[e.v]) {
            continue;
        }

        // Verificar que no forme ciclo
        if (dsu.find(e.u) == dsu.find(e.v)) {
            continue;
        }

        // Si es la última arista, agregar directamente
        if ((int)result.tree.edges.size() == G.n - 2) {
            result.tree.addEdge(e);
            deg[e.u]++;
            deg[e.v]++;
            dsu.merge(e.u, e.v);
            result.last_edge_index = k;
            result.success = true;
            break;
        }

        // Verificar condición de no saturación
        // Obtener componentes
        std::vector<int> comp_u, comp_v;
        for (int i = 0; i < G.n; i++) {
            if (dsu.find(i) == dsu.find(e.u)) {
                comp_u.push_back(i);
            } else if (dsu.find(i) == dsu.find(e.v)) {
                comp_v.push_back(i);
            }
        }

        int delta_u = treeDegree(comp_u, deg);
        int delta_v = treeDegree(comp_v, deg);
        int cap_u = treeCapacity(comp_u, G.b);
        int cap_v = treeCapacity(comp_v, G.b);

        // Condición de no saturación: delta(T1) + delta(T2) + 2 <= d(T1) + d(T2)
        // Usamos <= en lugar de < para ser menos restrictivo
        if (delta_u + delta_v + 2 <= cap_u + cap_v) {
            result.tree.addEdge(e);
            deg[e.u]++;
            deg[e.v]++;
            dsu.merge(e.u, e.v);
            result.last_edge_index = k;
        }
    }

    result.success = ((int)result.tree.edges.size() == G.n - 1);
    return result;
}