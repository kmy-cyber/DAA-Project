#pragma once
#include <vector>
#include "../utils/graph.hpp"

// Compute transitive closure avoiding a specific vertex (Floyd-Warshall O(n^3))
std::vector<std::vector<bool>> transitiveClosureAvoidVertex(const Graph& G, int avoid) {
    int n = G.n;
    std::vector<std::vector<bool>> reach(n, std::vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        if (i == avoid) continue;
        for (int j : G.adj[i]) {
            if (j == avoid) continue;
            reach[i][j] = true;
        }
    }

    // Floyd-Warshall 
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


