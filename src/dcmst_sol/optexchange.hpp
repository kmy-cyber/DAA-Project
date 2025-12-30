#pragma once
#include "../utils/graph.hpp"
#include "../utils/types.hpp"


// obtener el camino u-v en el arbol
bool getPathBFS(
    int n,
    const std::vector<vEdges>& adj,
    int src,
    int dst,
    vEdges& path
) {
    vi parent(n, -1);
    vEdges parentEdge(n);

    std::queue<int> q;
    q.push(src);
    parent[src] = src;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == dst) break;

        for (const auto& e : adj[u]) {
            int v = (e.u == u ? e.v : e.u);
            if (parent[v] != -1) continue;
            parent[v] = u;
            parentEdge[v] = e;
            q.push(v);
        }
    }

    if (parent[dst] == -1) return false;

    int cur = dst;
    while (cur != src) {
        path.push_back(parentEdge[cur]);
        cur = parent[cur];
    }

    return true;
}


void oneOptExchange(Graph& G, std::vector<Edge>& T) {
    int n = G.n;

    // grados
    vi degree(n, 0);
    for (const auto& e : T) {
        degree[e.u]++;
        degree[e.v]++;
    }

    std::vector<vEdges> treeAdj(n);
    for (const auto& e : T) {
        treeAdj[e.u].push_back(e);
        treeAdj[e.v].push_back(e);
    }

    // probar cada arista fuera del árbol
    for (const auto& e : G.edges) {

        //std::cout << "Trying edge: " << e.u << " " << e.v << " " << e.w << std::endl;

        vEdges path;
        if (!getPathBFS(n, treeAdj, e.u, e.v, path)) continue;

        // probar TODAS las aristas del ciclo
        for (const auto& rem : path) {

            if (rem.w <= e.w) continue;

            //std::cout << "Considering removing edge: " << rem.u << " " << rem.v << " " << rem.w << std::endl;

            int du = degree[e.u] + 1;
            int dv = degree[e.v] + 1;

            if (e.u == rem.u || e.u == rem.v) du--;
            if (e.v == rem.u || e.v == rem.v) dv--;

            if (du > G.b[e.u]) continue;
            if (dv > G.b[e.v]) continue;

            //  intercambio válido
            removeEdge(T, rem);
            G.addEdge(rem.u,rem.v,rem.w); 
            T.push_back(e);
            G.removeEdge(e.u,e.v);

            degree[rem.u]--;
            degree[rem.v]--;
            degree[e.u]++;
            degree[e.v]++;

            return;
        }
    }
}





void twoOptExchange(const Graph& G, vEdges& T) {
    
    bool improved = true;

    while (improved) {
        improved = false;

        for (size_t i = 0; i < T.size() && !improved; i++) {
            for (size_t j = i + 1; j < T.size(); j++) {

                Edge e1 = T[i];
                Edge e2 = T[j];

                int a = e1.u, b = e1.v;
                int c = e2.u, d = e2.v;

                
                if (!G.hasEdge(a, c) || !G.hasEdge(b, d)) continue;

                
                if (edgeInTree(T, a, c)) continue;
                if (edgeInTree(T, b, d)) continue;

                int wOld = e1.w + e2.w;
                int wNew = G.getWeight(a, c) + G.getWeight(b, d);

                if (wNew >= wOld) continue;

                vEdges Ttmp;
                for (size_t k = 0; k < T.size(); k++) {
                    if (k != i && k != j)
                        Ttmp.push_back(T[k]);
                }

                if (connected(a, c, Ttmp,G.n)) continue;

                if (connected(b, d, Ttmp,G.n)) continue;

                Ttmp.push_back({a, c, G.getWeight(a, c)});
                Ttmp.push_back({b, d, G.getWeight(b, d)});

                T = Ttmp;
                improved = true;
                break;
            }
        }
    }
}