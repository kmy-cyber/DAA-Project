#pragma once
#include <vector>
#include <queue>
#include <stack>
#include "types.hpp"

struct Edge {
    int u, v, w;
};

typedef std::vector<Edge> vEdges;

bool edgeInTree(const vEdges& T, int u, int v) {
    for (const auto& e : T) {
        if ((e.u == u && e.v == v) ||
            (e.u == v && e.v == u)) {
            return true;
        }
    }
    return false;
}

bool connected(int u, int v, const vEdges& T, int n) {
    vvi adj(n);

    for (const auto& e : T) {
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }

    std::vector<bool> visited(n, false);
    std::stack<int> st;

    st.push(u);
    visited[u] = true;

    while (!st.empty()) {
        int x = st.top(); st.pop();
        if (x == v) return true;

        for (int nx : adj[x]) {
            if (!visited[nx]) {
                visited[nx] = true;
                st.push(nx);
            }
        }
    }
    return false;
}


void removeEdge(vEdges& T, const Edge& e) {
    for (auto it = T.begin(); it != T.end(); ++it) {
        if ((it->u == e.u && it->v == e.v && it->w == e.w) ||
            (it->u == e.v && it->v == e.u && it->w == e.w)) {
            T.erase(it);
            return;
        }
    }
}
