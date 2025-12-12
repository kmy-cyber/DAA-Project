#pragma once
#include <vector>
#include <numeric>
#include "types.hpp"


struct DSU {

    vi parent;

    DSU(int n) : parent(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x){
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    bool merge(int a , int b){
        a = find(a);
        b = find(b);

        if(a == b) return false;

        parent[a] = b;

        return true;
    }
};