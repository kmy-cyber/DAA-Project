#include <bits/stdc++.h>
using namespace std;

using vii = vector<pair<int,int>>; // vecino, costo
using Edge = tuple<int,int,int>; // u,v,costo

int main(){
    int n,m,k;
    cin >> n >> m >> k;

    vector<vii> g(n);
    for(int i=0;i<m;i++){
        int u,v,c;
        cin >> u >> v >> c;
        g[u].push_back({v,c});
        g[v].push_back({u,c});
    }

    vector<Edge> edges;
    for(int u=0; u<n; u++)
        for(auto &[v,c] : g[u])
            if(u < v) edges.push_back({u,v,c});

    int sz = edges.size();
    vector<Edge> bestTree;
    int minCost = INT_MAX;

    for(int mask=0; mask < (1<<sz); mask++){
        if(__builtin_popcount(mask) != n-1) continue;

        vector<Edge> candidate;
        for(int i=0; i<sz; i++)
            if(mask & (1<<i)) candidate.push_back(edges[i]);

        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);
        auto find = [&](int x) {
            while(parent[x]!=x) x=parent[x];
            return x;
        };
        auto unite = [&](int x,int y){
            int fx=find(x), fy=find(y);
            if(fx==fy) return false;
            parent[fx]=fy;
            return true;
        };

        vector<int> deg(n,0);
        bool valid=true;
        int cost=0;
        for(auto &[u,v,c] : candidate){
            if(deg[u]+1>k || deg[v]+1>k){ valid=false; break; }
            deg[u]++; deg[v]++;
            if(!unite(u,v)){ valid=false; break; }
            cost+=c;
        }

        if(valid && cost<minCost){
            minCost=cost;
            bestTree=candidate;
        }
    }

    if(bestTree.empty())
        cout << "No existe árbol con grado <= " << k << endl;
    else{
        cout << "Costo mínimo: " << minCost << endl;
        for(auto &[u,v,c] : bestTree)
            cout << u << " " << v << " (c=" << c << ")\n";
    }
}
