#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    unsigned seed = 47;           // valor por defecto
    if (argc > 1) seed = atoi(argv[1]);
    mt19937 rng(seed);

    int n = 10 + rng()%10;          // nodos
    int m = n + rng()%10;           // aristas
    cout << n << " " << m << "\n";

    vector<vector<int>> adj(n,vector<int>(n,0));

    vector<tuple<int,int,int>> edges;
    
    for(int i=0;i<m;i++){
        int u = rng()%n;
        int v = rng()%n;
        while(v==u || adj[u][v]!=0) v = rng()%n;

        adj[u][v]=1;

        int w = 1 + rng()%20;
        edges.emplace_back(u,v,w);
        cout << u << " " << v << " " << w << "\n";
    }

    for(int i=0;i<n;i++){
        cout << 1 + rng()%3 << " ";
    }
    cout << "\n";
}
