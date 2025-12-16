#pragma once
#include <bits/stdc++.h>
#include "edge.hpp"
#include "dsu.hpp"
#include "types.hpp"

// itera por todos los conjuntos de aristas, verifica que comprueba las restricciones
// si las cumples, entonces actualiza con la mejor solucion encontrada
std::pair<ll, vEdges> 
degreeConstrainedMST(int n, 
                     const vEdges& edges,
                     const vi& maxDeg)
{
    int m = edges.size();
    ll bestCost = LLONG_MAX;
    vEdges bestTree;

    for(int mask = 0; mask < (1 << m); mask++) {

        //verifica que el conjunto de aristas tomado tenga n-1 aristas
        if (__builtin_popcount(mask) != n - 1)
            continue;

        vEdges cand;
        for(int i = 0; i < m; i++)
            if(mask & (1 << i))
                cand.push_back(edges[i]);

        DSU dsu(n);
        vi deg(n,0);
        ll cost = 0;
        bool valid = true;

        // comprueba que es conexo
        for(auto &e : cand) {
            if(deg[e.u]+1 > maxDeg[e.u] ||
               deg[e.v]+1 > maxDeg[e.v]) {
                valid = false; 
                break;
            }

            deg[e.u]++; deg[e.v]++;

            if(!dsu.merge(e.u, e.v)) {
                valid = false; 
                break;
            }

            cost += e.c;
        }

        if(valid && cost < bestCost) {
            bestCost = cost;
            bestTree = cand;
        }
    }

    return {bestCost, bestTree};
}
