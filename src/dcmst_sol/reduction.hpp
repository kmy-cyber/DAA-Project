#pragma once
#include <vector>
#include "../utils/graph.hpp"

// Theorem 1: Include all edges of pendant vertices to T* and remove them from G
   

// Theorem 2: Remove all edges between vertices with b = 1 (E1)
void removeEdgesBetweenB1Vertices(Graph& G) {
    
    if(G.n <=2 ) return ;

    for(int i = 0; i < G.n; i++) {
        for(int j = i+1; j < G.n; j++) {
            if(G.b[i]==1 && G.b[j]==1)
            {
                G.removeEdge(i,j);
            }
        }
    }
}


bool bfsAvoidVertex(const Graph& G , int start, int end, int avoid)
{
    std::vector<bool>visited(G.n,false);
    std::queue<int>q;


    visited[avoid]= visited[start]=true;
    q.push(start);

    while(!q.empty())
    {
        int curr = q.front(); q.pop();

        for(const auto& p : G.adj[curr])
        {
            int neighbor = p.first;
            if(!visited[neighbor])
            {
                if(neighbor==end)return true;
                visited[neighbor]= true;
                q.push(neighbor);
            }
        }
    }

    return false;
}

// Include all critical edges for degree-2 vertices based on Theorem 3
// If there is no alternative path between its neighbors, include its edges in T*




void Reduction_DCMST(Graph& G, std::vector<Edge>& T) {
    
    removeEdgesBetweenB1Vertices(G);

    std::queue<int> q;
    std::vector<bool> inQueue(G.n, false);

    for (int v = 0; v < G.n; v++) {
        if (G.degree[v] == 1 || G.degree[v] == 2) {
            q.push(v);
            inQueue[v] = true;
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        inQueue[v] = false;

        // Theorem 1: grado 1
        if (G.degree[v] == 1) {
            int u = G.adj[v][0].first;
            int w = G.adj[v][0].second;
            if (G.removeEdge(v, u)) {
                T.push_back(Edge{u, v, w});
                // Verificar si el vecino se convierte en grado 1 o 2
                if ((G.degree[u] == 1 || G.degree[u] == 2) && !inQueue[u]) {
                    q.push(u);
                    inQueue[u] = true;
                }
            }
        }

        // Theorem 3: grado 2
        else if (G.degree[v] == 2) {
            int u = G.adj[v][0].first;
            int w = G.adj[v][1].first;
            if (!bfsAvoidVertex(G, u, w, v)) {
               
                int w_uv = G.adj[v][0].second;
                int w_vw = G.adj[v][1].second;

                T.push_back(Edge{u, v, w_uv});
                T.push_back(Edge{v, w, w_vw});
                G.removeEdge(v, u);
                G.removeEdge(v, w);

                // Verificar si vecinos se convierten en grado 1 o 2
                for (int x : {u, w}) {
                    if ((G.degree[x] == 1 || G.degree[x] == 2) && !inQueue[x]) {
                        q.push(x);
                        inQueue[x] = true;
                    }
                }
            }
        }

    }

}