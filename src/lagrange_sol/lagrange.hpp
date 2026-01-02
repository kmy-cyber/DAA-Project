#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include "../utils/graph.hpp"
#include "../utils/dsu.hpp"
#include "../utils/edge.hpp"
#include "spanningTree.hpp"

/* ========================================
   Cálculo de saturación de un árbol
   ======================================== */
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
struct KruskalResult {
    SpanningTree tree;
    int last_edge_index;
    bool success;

    KruskalResult(int n) : tree(n), last_edge_index(-1), success(false) {}
};

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

/* ========================================
   Procedimiento de Mejora Local
   ======================================== */
void improvementProcedure(SpanningTree& tree, const Graph& G) {
    bool improved = true;
    int max_iterations = 100;
    int iter = 0;

    while (improved && iter < max_iterations) {
        improved = false;
        iter++;

        vEdges original_edges = tree.edges;

        for (const Edge& e : original_edges) {
            // Remover arista e
            tree.removeEdge(e.u, e.v);

            // Encontrar componentes
            DSU dsu(G.n);
            for (const Edge& te : tree.edges) {
                dsu.merge(te.u, te.v);
            }

            int comp_u = dsu.find(e.u);
            int comp_v = dsu.find(e.v);

            // Buscar mejor arista de reconexión
            Edge best_edge = {-1, -1, std::numeric_limits<int>::max()};
            bool found = false;

            for (const Edge& candidate : G.edges) {
                int comp_cu = dsu.find(candidate.u);
                int comp_cv = dsu.find(candidate.v);

                // Debe conectar las dos componentes
                if (!((comp_cu == comp_u && comp_cv == comp_v) || 
                      (comp_cu == comp_v && comp_cv == comp_u))) {
                    continue;
                }

                // Verificar restricciones de grado
                int deg_u = tree.degree[candidate.u];
                int deg_v = tree.degree[candidate.v];

                // Si la arista conecta un extremo de e, puede reutilizar ese grado
                bool u_is_endpoint = (candidate.u == e.u || candidate.u == e.v);
                bool v_is_endpoint = (candidate.v == e.u || candidate.v == e.v);

                if (!u_is_endpoint && deg_u >= G.b[candidate.u]) continue;
                if (!v_is_endpoint && deg_v >= G.b[candidate.v]) continue;

                // Verificar que sea mejor
                if (candidate.w < best_edge.w) {
                    best_edge = candidate;
                    found = true;
                }
            }

            // Aplicar intercambio si mejora
            if (found && best_edge.w < e.w) {
                tree.addEdge(best_edge);
                improved = true;
            } else {
                // Restaurar arista original
                tree.addEdge(e);
            }
        }
    }
}

/* ========================================
   Construcción greedy simple como fallback
   ======================================== */
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

/* ========================================
   Heurística Lagrangiana Principal
   ======================================== */
void lagrangianHeuristic(const Graph& G, vEdges& result) {
    const int n = G.n;
    const int m = G.edges.size();

    // Inicialización
    std::vector<double> lambda(n, 0.0);
    std::vector<double> costs(m);
    
    // Costos originales
    for (int i = 0; i < m; i++) {
        costs[i] = G.edges[i].w;
    }

    // Solución inicial con KRUSKALX
    KruskalResult initial = kruskalX(G, costs);
    
    ll z_UB = std::numeric_limits<ll>::max();
    double z_LB = -std::numeric_limits<double>::max();
    SpanningTree best_tree(n);
    bool found_feasible = false;

    if (initial.success && initial.tree.isFeasible(G.b)) {
        best_tree = initial.tree;
        z_UB = best_tree.cost();
        found_feasible = true;
    } else {
        // Intentar con greedy simple
        SpanningTree greedy = simpleGreedy(G);
        if (greedy.isFeasible(G.b)) {
            best_tree = greedy;
            z_UB = best_tree.cost();
            found_feasible = true;
        } else {
            // Intentar con múltiples inicializaciones aleatorias
            std::vector<double> shuffled_costs(m);
            for (int attempt = 0; attempt < 10 && !found_feasible; attempt++) {
                // Perturbar costos ligeramente
                for (int i = 0; i < m; i++) {
                    shuffled_costs[i] = costs[i] * (1.0 + 0.01 * (attempt - 5));
                }
                
                SpanningTree perturbed = simpleGreedy(G, &shuffled_costs);
                if (perturbed.isFeasible(G.b)) {
                    best_tree = perturbed;
                    z_UB = best_tree.cost();
                    found_feasible = true;
                    break;
                }
            }
        }
    }

    // Crear problema restringido
    int m_restricted = std::min(2 * std::max(initial.last_edge_index + 1, 10), m);
    
    // Si no encontramos solución factible inicial, usar una solución parcial mejor que nada
    if (!found_feasible) {
        // Intentar con la mejor solución parcial que tengamos
        if (initial.tree.edges.size() > 0) {
            best_tree = initial.tree;
            z_UB = std::numeric_limits<ll>::max() / 2; // Valor alto para forzar búsqueda
        } else {
            // Como último recurso, devolver vacío
            result.clear();
            return;
        }
    }
    
    // Parámetros del método del subgradiente
    double alpha = 2.0;
    const int max_iter = 500;
    int iter_without_improvement = 0;

    for (int iter = 0; iter < max_iter; iter++) {
        // Calcular costos modificados: c_e + lambda_i + lambda_j
        for (int i = 0; i < m; i++) {
            const Edge& e = G.edges[i];
            costs[i] = e.w + lambda[e.u] + lambda[e.v];
        }

        // Resolver LRS (MST con costos modificados)
        SpanningTree lrs_tree = classicMST(G, costs);

        // Calcular cota inferior
        double z_lambda = 0.0;
        for (const Edge& e : lrs_tree.edges) {
            z_lambda += e.w + lambda[e.u] + lambda[e.v];
        }
        for (int i = 0; i < n; i++) {
            z_lambda -= lambda[i] * G.b[i];
        }

        if (z_lambda > z_LB) {
            z_LB = z_lambda;
            iter_without_improvement = 0;
        } else {
            iter_without_improvement++;
        }

        // Si LRS es factible para DC-MST
        if (lrs_tree.isFeasible(G.b)) {
            improvementProcedure(lrs_tree, G);
            ll cost = lrs_tree.cost();
            if (cost < z_UB) {
                z_UB = cost;
                best_tree = lrs_tree;
            }
        }

        // Construcción heurística con costos complementarios
        std::vector<double> comp_costs(m);
        for (int i = 0; i < m; i++) {
            const Edge& e = G.edges[i];
            double x_e = 0.0;
            
            // Verificar si la arista está en lrs_tree
            for (const Edge& te : lrs_tree.edges) {
                if ((te.u == e.u && te.v == e.v) || (te.u == e.v && te.v == e.u)) {
                    x_e = 1.0;
                    break;
                }
            }
            
            comp_costs[i] = (1.0 - x_e) * e.w;
        }

        KruskalResult heur_result = kruskalX(G, comp_costs);
        if (heur_result.success && heur_result.tree.isFeasible(G.b)) {
            improvementProcedure(heur_result.tree, G);
            ll cost = heur_result.tree.cost();
            if (cost < z_UB) {
                z_UB = cost;
                best_tree = heur_result.tree;
            }
        } else {
            // Intentar greedy simple con costos complementarios
            SpanningTree greedy = simpleGreedy(G, &comp_costs);
            if (greedy.isFeasible(G.b)) {
                improvementProcedure(greedy, G);
                ll cost = greedy.cost();
                if (cost < z_UB) {
                    z_UB = cost;
                    best_tree = greedy;
                }
            }
        }
        
        // Intentar con costos Lagrangianos también
        if (iter % 10 == 0) {
            SpanningTree lagr_greedy = simpleGreedy(G, &costs);
            if (lagr_greedy.isFeasible(G.b)) {
                improvementProcedure(lagr_greedy, G);
                ll cost = lagr_greedy.cost();
                if (cost < z_UB) {
                    z_UB = cost;
                    best_tree = lagr_greedy;
                }
            }
        }

        // Criterio de parada
        if (z_UB - z_LB < 0.99) {
            break;
        }

        // Actualizar multiplicadores Lagrangianos
        vi subgradient(n);
        double norm_sq = 0.0;
        
        for (int i = 0; i < n; i++) {
            subgradient[i] = lrs_tree.degree[i] - G.b[i];
            norm_sq += subgradient[i] * subgradient[i];
        }

        if (norm_sq > 0.0) {
            double step = alpha * (z_UB - z_lambda) / norm_sq;
            
            for (int i = 0; i < n; i++) {
                if (subgradient[i] > 0 || lambda[i] > 0) {
                    lambda[i] = std::max(0.0, lambda[i] + step * subgradient[i]);
                }
            }
        }

        // Ajustar alpha
        if (iter_without_improvement > 30) {
            alpha *= 0.5;
            iter_without_improvement = 0;
        }
    }

    // Retornar mejor solución encontrada (solo si es factible)
    if (best_tree.isFeasible(G.b) && best_tree.edges.size() == (size_t)(G.n - 1)) {
        result = best_tree.edges;
    } else {
        result.clear();
    }
}
