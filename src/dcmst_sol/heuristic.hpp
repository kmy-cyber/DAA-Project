#pragma once
#include "../utils/graph.hpp"
#include "../utils/types.hpp"
#include "../utils/dsu.hpp"
#include <map>


bool connectComponentsHeuristicAdvanced(Graph& G, vEdges& T) {
    int n = G.n;
    DSU dsu(n);
    std::vector<int> degree(n, 0);

    for (auto &e : T) {
        dsu.merge(e.u, e.v);
        degree[e.u]++;
        degree[e.v]++;
    }

    if ((int)T.size() == n-1) return true;

    //dsu.print_dsu();

    std::map<int,vi> nonSaturated;
    for (int i = 0; i < n; i++) {
        if (degree[i] < G.b[i])
            nonSaturated[dsu.find(i)].push_back(i);
    }


    for ( auto& e : T)
    {
        if (degree[e.u] < G.b[e.u] || degree[e.v] < G.b[e.v]) continue;


        int comp = dsu.find(e.u);

        for(auto& [key, nodes] : nonSaturated)
        {

            if(key == comp) continue;

            for (int x : nodes) {

                if (G.hasEdge(e.u, x) && G.hasEdge(e.v, x)
                    && degree[x] + 2 <= G.b[x]) {

                    
                    T.push_back({e.u, x, G.getWeight(e.u, x)});
                    //std::cout << "Adding edge: " << e.u << " " << x << std::endl;
                    G.removeEdge(e.u,x); 
                    T.push_back({e.v, x, G.getWeight(e.v, x)});
                    //std::cout << "Adding edge: " << e.v << " " << x << std::endl;
                    G.removeEdge(e.v,x);
                    removeEdge(T, e);
                    //std::cout << "Removing edge: " << e.u << " " << e.v << std::endl;
                    G.addEdge(e.u,e.v,e.w); 
                    
                    
                    return true;
                }
            }

            for (int x : nodes) {
                if (!G.hasEdge(e.u, x) || degree[x] + 1 > G.b[x]) continue;

                for (int y : nodes) {
                    if (x == y) continue;
                    if (!G.hasEdge(e.v, y) || degree[y] + 1 > G.b[y]) continue;

                    
                    T.push_back({e.u, x, G.getWeight(e.u, x)});
                    T.push_back({e.v, y, G.getWeight(e.v, y)});
                    removeEdge(T, e);
                    G.addEdge(e.u,e.v,e.w); 

                    return true;
                }
            }
        
        }
    }

    return false; // No se pudo conectar
}
