#pragma once
#include <vector>
#include "transitive_closure.hpp"

// Agrega todas las aristas de vértices de grado 1 al árbol y los elimina del grafo
void includePendantVerticesEdges(Graph& G, std::vector<std::pair<int,int>>& T) {
    for(int u=0; u<G.n; u++){
        if(G.degree[u]==1){
            for(int v=0; v<G.n; v++){
                if(G.adj[u][v]){
                    T.push_back({u,v}); // agregar al árbol
                    G.adj[u][v]=0;
                    G.adj[v][u]=0;
                    G.degree[u]--; G.degree[v]--;
                }
            }
        }
    }
}


// Elimina aristas entre vértices de grado 1
void removeEdgesBetweenPendantVertices(Graph& G) {
    for(int u=0; u<G.n; u++){
        if(G.degree[u]==1){
            for(int v=0; v<G.n; v++){
                if(G.degree[v]==1 && G.adj[u][v]){
                    G.adj[u][v]=0;
                    G.adj[v][u]=0;
                }
            }
        }
    }
}


// Para vértices de grado 2, si no hay camino alternativo entre sus vecinos, agrega las aristas
void includeDegreeTwoCriticalEdges(Graph& G, std::vector<std::pair<int,int>>& T) {
    for(int v=0; v<G.n; v++){
        if(G.degree[v]==2){
            std::vector<int> neighbors;
            for(int u=0; u<G.n; u++)
                if(G.adj[v][u]) neighbors.push_back(u);
            if(neighbors.size()!=2) continue;
            int u = neighbors[0], w = neighbors[1];
            auto reach = transitiveClosureAvoidVertex(G, v);
            if(!reach[u][w]){
                // No hay camino alternativo: añadir aristas
                T.push_back({v,u});
                T.push_back({v,w});
                G.adj[v][u]=0; G.adj[u][v]=0;
                G.adj[v][w]=0; G.adj[w][v]=0;
                G.degree[v]=0; G.degree[u]--; G.degree[w]--;
            }
        }
    }
}



void Reduction_DCMST(Graph& G, std::vector<std::pair<int,int>>& T) {
    // 1. Eliminar aristas entre vértices colgantes (Theorem 2)
    removeEdgesBetweenPendantVertices(G);

    // 2. Incluir aristas de vértices colgantes al árbol y eliminarlas del grafo (Theorem 1)
    includePendantVerticesEdges(G, T);

    // 3. Incluir aristas críticas de vértices de grado 2 (Theorem 3)
    includeDegreeTwoCriticalEdges(G, T);
}