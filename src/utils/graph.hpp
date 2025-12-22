#pragma once
#include <vector>
#include <algorithm>
#include "edge.hpp"

struct Graph {
    int n;

    std::vector<std::vector<std::pair<int, int>>> adj;  // pair<vertex, weight>

    std::vector<int> degree;

    std::vector<Edge> edges;

    std::vector<int> b;

    Graph(int n)
        : n(n),
          adj(n),
          degree(n, 0),
          b(n, 0) {}

    bool hasEdge(int u, int v) const {
        for (const auto& p : adj[u]) {
            if (p.first == v) return true;
        }
        return false;
    }

    int getWeight(int u, int v) const {
        for (const auto& p : adj[u]) {
            if (p.first == v) return p.second;
        }
        return -1;  // edge not found
    }

    void addEdge(int u, int v, int w) {
        if (hasEdge(u, v)) return;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        degree[u]++;
        degree[v]++;
        edges.push_back({u, v, w});
    }

    bool removeEdge(int u, int v) {
        if (!hasEdge(u, v)) return false;

        // eliminar de adj
        adj[u].erase(std::remove_if(adj[u].begin(), adj[u].end(),
            [v](const std::pair<int, int>& p) { return p.first == v; }),
            adj[u].end());
        adj[v].erase(std::remove_if(adj[v].begin(), adj[v].end(),
            [u](const std::pair<int, int>& p) { return p.first == u; }),
            adj[v].end());

        degree[u]--;
        degree[v]--;

        // eliminar de edges
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                [&](const Edge& e) {
                    return (e.u == u && e.v == v) || (e.u == v && e.v == u);
                }),
            edges.end()
        );

        return true;
    }
};
