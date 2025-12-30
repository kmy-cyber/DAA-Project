#pragma once
#include <iostream>
#include "graph.hpp"
#include "types.hpp"

namespace IO {

    inline Graph readGraphFromStdin() {
        int n, m;
        std::cin >> n >> m;

        Graph G(n);

        for (int i = 0; i < m; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;
            G.addEdge(u, v, w);
        }

        for (int i = 0; i < n; i++) {
            std::cin >> G.b[i];
        }

        return G;
    }

    inline void printSolution(const std::vector<Edge>& T) {
        if (T.empty()) {
            std::cout << "-1\n";
            return;
        }

        ll cost = 0;
        for (auto& e : T) cost += e.w;

        std::cout << cost << "\n";
        for (auto& e : T)
            std::cout << e.u << " " << e.v << " " << e.w << "\n";
    }

}
