#pragma once
#include <vector>
#include "types.hpp"


struct DSU {
    
    vi parent, rank;

    DSU(int n) : parent(n), rank(n,0) { std::iota(parent.begin(), parent.end(), 0);}

    int find(int u) {
        if(parent[u] != u) parent[u] = find(parent[u]);
        return parent[u];
    }

    bool merge(int a , int b){
        a = find(a);
        b = find(b);

        if(a == b) return false;

        if(rank[a] < rank[b]) std::swap(a,b);

        parent[b] = a;

        if(rank[a]==rank[b]) rank[a]++;

        return true;
    }
};