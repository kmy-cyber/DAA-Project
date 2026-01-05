#pragma once
#include <vector>
#include <numeric>
#include <iostream>
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

    void print_dsu()
    {
        for(int i=0;i<(int)parent.size();i++)
        {
            std::cout << "Node: " << i << " Parent: " << parent[i] 
                      << " Rank: " << rank[i] << std::endl;
        }
    }

    int getNumComponents()
    {
        int components = 0;
        for(int i = 0; i < (int)parent.size(); i++)
            if(find(i) == i)
                components++;
        return components;
    }
};