#pragma once
#include <bits/stdc++.h>
#include "dsu.hpp"
using namespace std;

bool checkSolution(
    int n,
    const vector<int>& maxDeg,
    const vector<tuple<int,int,int>>& tree,
    long long reportedCost
) {
    if ((int)tree.size() != n - 1) return false;

    vector<int> deg(n, 0);
    long long cost = 0;

    DSU dsu(n);

    for (auto &[u, v, c] : tree) {
        if (u < 0 || u >= n || v < 0 || v >= n) return false;
        deg[u]++;
        deg[v]++;
        cost += c;
        dsu.merge(u, v);
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] > maxDeg[i]) return false;
        if (dsu.find(i) != dsu.find(0)) return false;
    }

    return cost == reportedCost;
}
