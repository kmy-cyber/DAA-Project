#pragma once
#include <vector>
#include <algorithm>
#include <numeric> 
#include <climits>
#include <queue>
#include "../utils/graph.hpp"
#include "../utils/dsu.hpp"
#include "reduction.hpp"


void buildDegreeConstrainedMST(Graph& G, std::vector<Edge>& T) {
    // Ordenar aristas por peso
    std::vector<Edge> sortedEdges = G.edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(),
              [](const Edge& a, const Edge& b) { return a.w < b.w; });

    // std::cout << "buildDegreeConstrainedMST" << std::endl;

    // for(const auto&v : sortedEdges)
    // {
    //     std::cout << v.u << " " << v.v << " " << v.w << std::endl;
    // }

    DSU dsu(G.n);
    std::vector<int> degT(G.n, 0);

    for(const auto& v : T)
    {
        dsu.merge(v.u,v.v);
        degT[v.u]++;
        degT[v.v]++;
    }

    // for(const auto& v : degT) std::cout << v <<  " " ;

    // std::cout << std::endl;

    // for(int i=0;i<dsu.parent.size();i++) std::cout << dsu.parent[i] << " ";

    // std::cout << std::endl;

    for(const auto& e : sortedEdges)
    {
        if(dsu.find(e.u) != dsu.find(e.v) && degT[e.u] < G.b[e.u] && degT[e.v] < G.b[e.v])
        {
            T.push_back({e.u,e.v,e.w});
            dsu.merge(e.u,e.v);
            degT[e.u]++;
            degT[e.v]++;
        }

        if((int)T.size() == G.n - 1) break;
    }

}

bool edgeInTree(const std::vector<Edge>& T, int u, int v) {
    for (const auto& e : T) {
        if ((e.u == u && e.v == v) ||
            (e.u == v && e.v == u)) {
            return true;
        }
    }
    return false;
}


bool connectedWithoutEdge(
    const std::vector<Edge>& T,
    int start,
    int target,
    int skip_u,
    int skip_v,
    int n
) {
    std::vector<std::vector<int>> adj(n);
    for (auto& e : T) {
        if ((e.u == skip_u && e.v == skip_v) ||
            (e.u == skip_v && e.v == skip_u))
            continue;

        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }

    std::queue<int> q;
    std::vector<bool> vis(n, false);

    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == target) return true;

        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

void oneOptExchange(const Graph& G, std::vector<Edge>& T) {
    bool improved = true;

    while (improved) {
        improved = false;

        for (size_t i = 0; i < T.size() && !improved; i++) {
            Edge oldEdge = T[i];
            int wOld = oldEdge.w;

            // Probar cada arista externa
            for (const auto& e : G.edges) {
                int a = e.u, b = e.v;

                if (edgeInTree(T, a, b)) continue;

                if (connectedWithoutEdge(T, a, b, oldEdge.u , oldEdge.v, G.n))
                    continue;  


                if (e.w < wOld) {
                    T[i] = e;
                    improved = true;
                    break;
                }
            }
        }
    }
}

void twoOptExchange(const Graph& G, std::vector<Edge>& T) {
    bool improved = true;

    while (improved) {
        improved = false;

        for (size_t i = 0; i < T.size() && !improved; i++) {
            for (size_t j = i + 1; j < T.size(); j++) {

                Edge e1 = T[i];
                Edge e2 = T[j];

                int a = e1.u, b = e1.v;
                int c = e2.u, d = e2.v;

                // Nuevas aristas
                if (!G.hasEdge(a, c) || !G.hasEdge(b, d)) continue;
                if (edgeInTree(T, a, c) || edgeInTree(T, b, d)) continue;

                if (connectedWithoutEdge(T, a, c, a, b, G.n)) continue;
                if (connectedWithoutEdge(T, a, c, c, d, G.n)) continue;

                int wOld = e1.w + e2.w;

                int w_ac = G.getWeight(a, c);
                int w_bd = G.getWeight(b, d);

                int wNew = w_ac + w_bd;

                if (wNew < wOld) {
                    T[i] = {a, c, w_ac};
                    T[j] = {b, d, w_bd};
                    improved = true;
                    break;
                }
            }
        }
    }
}


void Main_DCMST(Graph& G, std::vector<Edge>& T) {
    
    Reduction_DCMST(G,T);

    // std::cout << "Initial T: " << std::endl;
    // for(const auto& v : T)
    // {
    //     std::cout << v.first << " " << v.second << std::endl;
    // }

    // std::cout << "End T of Reduction: " << std::endl;


    // std::cout << "Initial G: " << std::endl;
    // for(const auto& v : G.edges)
    // {
    //     std::cout << v.u << " " << v.v << std::endl;
    // }

    // std::cout << "End G of Reduction: " << std::endl;
    
    buildDegreeConstrainedMST(G, T);

    // std::cout << "Build Degree T: " << std::endl;

    // for(const auto& v : T)
    // {
    //     std::cout << v.first << " " << v.second << std::endl;
    // }

    // std::cout << "End T of buildDegree: " << std::endl;

    oneOptExchange(G, T);

    twoOptExchange(G, T);
}
