#include <bits/stdc++.h>
#include "graph.hpp"
#include "reduction.hpp"
using namespace std;

int main()
{
    int n = 5;
    Graph G(n);
    vector<pair<int,int>> T;

    // Ejemplo simple de inicialización
    G.adj[0][1]=G.adj[1][0]=1; G.degree[0]++; G.degree[1]++;
    G.adj[1][2]=G.adj[2][1]=1; G.degree[1]++; G.degree[2]++;
    G.adj[2][3]=G.adj[3][2]=1; G.degree[2]++; G.degree[3]++;
    G.adj[3][4]=G.adj[4][3]=1; G.degree[3]++; G.degree[4]++;

    Reduction_DCMST(G, T);
    return 0;
}