#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    unsigned seed = 47; 
    if(argc > 1) seed = atoi(argv[1]);
    mt19937 rng(seed); 

    int n = 10 + rng() % 10;    
    int m = n + rng()%10;      
    double p = 0.3;                   
    int w_min = 1, w_max = 20;        
    uniform_real_distribution<double> prob_dist(0.0, 1.0);
    uniform_int_distribution<int> weight_dist(w_min, w_max);

    vector<tuple<int,int,int>> edges;
    vector<vector<int>> adj(n,vector<int>(n,0));
 

    // for(int u=0; u<n; u++){
    //     for(int v=u+1; v<n; v++){
    //         if(prob_dist(rng) < p){
    //             int w = weight_dist(rng);
    //             edges.emplace_back(u,v,w);
    //         }
    //     }
    // }


    for(int i=0;i<m;i++){
        int u = rng()%n;
        int v = rng()%n;
        while(v==u || adj[u][v]!=0) v = rng()%n;

        adj[u][v]=1;
        adj[v][u]=1;

        int w = 1 + rng()%20;
        edges.emplace_back(u,v,w);
        cout << u << " " << v << " " << w << "\n";
    }

    
    cout << n << " " << edges.size() << "\n";

    
    for(auto &[u,v,w] : edges){
        cout << u << " " << v << " " << w << "\n";
    }

   
    for(int i=0; i<n; i++){
        cout << 1 + rng() % 3 << " ";
    }
    cout << "\n";
}
