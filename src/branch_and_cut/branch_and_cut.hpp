#pragma once
#include "../utils/graph.hpp"
#include "../utils/dsu.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

/// Check if adding edge violates degree constraints
bool isFeasibleEdge(const Graph& G, const Edge& e) {
    return G.degree[e.u] < G.b[e.u] && G.degree[e.v] < G.b[e.v];
}

/// Add edge to tree T and update degrees
void addEdgeToTree(Graph& G, std::vector<Edge>& T, const Edge& e) {
    T.push_back(e);
    G.degree[e.u]++;
    G.degree[e.v]++;
}

/// Remove edge from tree T and update degrees
void removeEdgeFromTree(Graph& G, std::vector<Edge>& T, const Edge& e) {
    T.erase(std::remove_if(T.begin(), T.end(),
        [&](const Edge& x) { return (x.u == e.u && x.v == e.v) || (x.u == e.v && x.v == e.u); }),
        T.end());
    G.degree[e.u]--;
    G.degree[e.v]--;
}

/// Generate initial feasible spanning tree using randomized Kruskal + degree check
void generateInitialTree(Graph& G, std::vector<Edge>& T) {
    T.clear();
    DSU dsu(G.n);
    std::vector<Edge> edges = G.edges;

    std::shuffle(edges.begin(), edges.end(), std::mt19937(std::time(nullptr)));

    for (auto& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v) && isFeasibleEdge(G, e)) {
            addEdgeToTree(G, T, e);
            dsu.merge(e.u, e.v);
        }
        if ((int)T.size() == G.n - 1) break;
    }
}

/// Generate a neighbor solution by exchanging up to k edges
std::vector<Edge> generateNeighbor(Graph& G, const std::vector<Edge>& T, int k) {
    std::vector<Edge> neighbor = T;
    std::mt19937 rng(std::time(nullptr));

    // Randomly remove k edges
    std::vector<int> idx(neighbor.size());
    std::iota(idx.begin(), idx.end(), 0);
    std::shuffle(idx.begin(), idx.end(), rng);

    for (int i = 0; i < k && i < (int)neighbor.size(); ++i)
        removeEdgeFromTree(G, neighbor, neighbor[idx[i]]);

    // Rebuild tree using DSU and feasible edges
    DSU dsu(G.n);
    for (auto& e : neighbor) dsu.merge(e.u, e.v);

    std::vector<Edge> candidates;
    for (auto& e : G.edges) {
        if (std::find_if(neighbor.begin(), neighbor.end(),
            [&](const Edge& x) { return (x.u == e.u && x.v == e.v) || (x.u == e.v && x.v == e.u); })
            == neighbor.end() && isFeasibleEdge(G, e)) {
            candidates.push_back(e);
        }
    }
    std::shuffle(candidates.begin(), candidates.end(), rng);

    for (auto& e : candidates) {
        if (dsu.find(e.u) != dsu.find(e.v) && isFeasibleEdge(G, e)) {
            addEdgeToTree(G, neighbor, e);
            dsu.merge(e.u, e.v);
        }
        if ((int)neighbor.size() == G.n - 1) break;
    }

    return neighbor;
}

/// Local search using VND with 1-3 edge exchanges
void localSearchVND(Graph& G, std::vector<Edge>& T) {
    bool improved = true;

    while (improved) {
        improved = false;

        for (int k = 1; k <= 3; ++k) {
            auto neighbor = generateNeighbor(G, T, k);

            int costNeighbor = 0, costT = 0;
            for (auto& e : neighbor) costNeighbor += e.w;
            for (auto& e : T) costT += e.w;

            if (costNeighbor < costT) {
                T = neighbor;
                improved = true;
                break; // restart VND from k=1
            }
        }
    }
}

/// Main DCMST VNS algorithm
void SolveDCMST(Graph& G, std::vector<Edge>& T) {
    // Step 1: Generate initial feasible tree
    generateInitialTree(G, T);

    int kMax = 3;
    bool improvement = true;

    // Step 2: Variable Neighborhood Search
    while (improvement) {
        improvement = false;
        for (int k = 1; k <= kMax; ++k) {
            auto neighbor = generateNeighbor(G, T, k);
            localSearchVND(G, neighbor);

            int costNeighbor = 0, costT = 0;
            for (auto& e : neighbor) costNeighbor += e.w;
            for (auto& e : T) costT += e.w;

            if (costNeighbor < costT) {
                T = neighbor;
                improvement = true;
                break; // restart VNS from k=1
            }
        }
    }

    // Al final T tiene exactamente G.n - 1 aristas
}
