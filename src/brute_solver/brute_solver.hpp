#pragma once
#include <vector>
#include <climits>
#include "../utils/edge.hpp"
#include "../utils/dsu.hpp"
#include "../utils/types.hpp"
#include "../utils/graph.hpp"


void Main_Brute_Solver(Graph& G, std::vector<Edge>& T)
{
    int m = G.edges.size();
    int n = G.n;

    ll bestCost = LONG_MAX;

    //vEdges bestTree;

    for(int mask =0 ; mask < (1 << m) ; mask++)
    {
        if (__builtin_popcount(mask) != n - 1)
            continue;

        vEdges cand;
        for(int i = 0; i < m; i++)
            if(mask & (1 << i))
                cand.push_back(G.edges[i]);

        DSU dsu(n);
        vi deg(n,0);
        ll cost = 0;
        bool valid = true;


        for(auto &e : cand) {
            if(deg[e.u]+1 > G.b[e.u] ||
               deg[e.v]+1 > G.b[e.v]) {
                valid = false; 
                break;
            }

            deg[e.u]++; deg[e.v]++;

            if(!dsu.merge(e.u, e.v)) {
                valid = false; 
                break;
            }

            cost += e.w;
        }


        if(valid && cost < bestCost) {
            bestCost = cost;
            T = cand;
        }

    }


}
// // itera por todos los conjuntos de aristas, verifica que comprueba las restricciones
// // si las cumples, entonces actualiza con la mejor solucion encontrada
// std::pair<ll, vEdges> 
// degreeConstrainedMST(int n, 
//                      const vEdges& edges,
//                      const vi& maxDeg)
// {
//     int m = edges.size();
//     ll bestCost = LLONG_MAX;
//     vEdges bestTree;

//     for(int mask = 0; mask < (1 << m); mask++) {

//         //verifica que el conjunto de aristas tomado tenga n-1 aristas
//         if (__builtin_popcount(mask) != n - 1)
//             continue;

//         vEdges cand;
//         for(int i = 0; i < m; i++)
//             if(mask & (1 << i))
//                 cand.push_back(edges[i]);

//         DSU dsu(n);
//         vi deg(n,0);
//         ll cost = 0;
//         bool valid = true;

//         // comprueba que es conexo
//         for(auto &e : cand) {
//             if(deg[e.u]+1 > maxDeg[e.u] ||
//                deg[e.v]+1 > maxDeg[e.v]) {
//                 valid = false; 
//                 break;
//             }

//             deg[e.u]++; deg[e.v]++;

//             if(!dsu.merge(e.u, e.v)) {
//                 valid = false; 
//                 break;
//             }

//             cost += e.w;
//         }

//         if(valid && cost < bestCost) {
//             bestCost = cost;
//             bestTree = cand;
//         }
//     }

//     return {bestCost, bestTree};
// }
