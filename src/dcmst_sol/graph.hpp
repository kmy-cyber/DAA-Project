#pragma once
#include <vector>

struct Graph {
    int n;
    std::vector<std::vector<int>> adj; 
    std::vector<int> degree;      

    Graph(int n) : n(n), adj(n, std::vector<int>(n,0)), degree(n,0) {}
};