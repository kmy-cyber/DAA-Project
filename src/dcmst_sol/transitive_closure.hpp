#pragma once
#include <vector>
#include "graph.hpp"

// n = número de vértices
// adj = matriz de adyacencia del grafo (1 = arista, 0 = sin arista)
// avoid = vértice que NO debe aparecer en el camino (0-indexed)

// O(n^3)
std::vector<std::vector<bool>> transitiveClosureAvoidVertex(const Graph& G, int avoid) {
    // Inicializar matriz de alcance
    int n = G.n;
    std::vector<std::vector<bool>> reach(n, std::vector<bool>(n, false));

    // Copiar las aristas existentes, omitiendo el vértice "avoid"
    for (int i = 0; i < n; i++) {
        if (i == avoid) continue;
        for (int j = 0; j < n; j++) {
            if (j == avoid) continue;
            if (G.adj[i][j]) reach[i][j] = true;
        }
    }

    // Floyd-Warshall modificado
    for (int k = 0; k < n; k++) {
        if (k == avoid) continue; 
        for (int i = 0; i < n; i++) {
            if (i == avoid) continue;
            for (int j = 0; j < n; j++) {
                if (j == avoid) continue;
                if (reach[i][k] && reach[k][j])
                    reach[i][j] = true;
            }
        }
    }

    return reach;
}


