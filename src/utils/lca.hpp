#pragma once
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include "types.hpp"
#include "edge.hpp"

class TreeLCA {
private:
    int n, LOG;
    vi depth;

    // up[v][i] = ancestro 2^i de v
    vvi up;

    // maxEdge[v][i] = arista más pesada desde v hasta up[v][i]
   vvi maxEdge;

   std::vector<vEdges> upEdge;

    // lista de adyacencia: {vecino, peso}
    std::vector<vii> adj;

    // nodeMax[v][i] = nodo desde el cual sale la arista máxima
    vvi nodeMax;


    void dfs(int u, int p, int w) {
        up[u][0] = p;
        maxEdge[u][0] = w;
        nodeMax[u][0] = u;

        for (int i = 1; i < LOG; i++) {
            if (up[u][i-1] != -1) {
                up[u][i] = up[ up[u][i-1] ][i-1];
                if (maxEdge[u][i-1] >= maxEdge[ up[u][i-1] ][i-1]) {
                    maxEdge[u][i] = maxEdge[u][i-1];
                    nodeMax[u][i] = nodeMax[u][i-1];
                } else {
                    maxEdge[u][i] = maxEdge[ up[u][i-1] ][i-1];
                    nodeMax[u][i] = nodeMax[ up[u][i-1] ][i-1];
                }
            }
        }

        for (auto [v, wt] : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, wt);
        }
    }

public:
    TreeLCA(int n) : n(n) {
        LOG = std::ceil(std::log2(n)) + 1;
        depth.assign(n, 0);
        adj.assign(n, {});
        up.assign(n, vi(LOG, -1));
        maxEdge.assign(n, vi(LOG, 0));
        nodeMax.assign(n, vi(LOG, -1));

    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void build(int root = 0) {
        dfs(root, -1, 0);
    }

    // LCA clásico
    int lca(int u, int v) {
        if (depth[u] < depth[v]) std::swap(u, v);

        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i)) {
                u = up[u][i];
            }
        }

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }

    // Máximo peso en el camino u-v (O(log n))
    int getMaxWeightInPath(int u, int v) {
        int res = 0;

        if (depth[u] < depth[v]) std::swap(u, v);

        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i)) {
                res = std::max(res, maxEdge[u][i]);
                u = up[u][i];
            }
        }

        if (u == v) return res;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                res = std::max(res, maxEdge[u][i]);
                res = std::max(res, maxEdge[v][i]);
                u = up[u][i];
                v = up[v][i];
            }
        }

        res = std::max(res, maxEdge[u][0]);
        res = std::max(res, maxEdge[v][0]);

        return res;
    }

    Edge getMaxEdge(int u, int v) {
        int bestW = -1;
        int bestNode = -1;

        if (depth[u] < depth[v]) std::swap(u, v);

        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i)) {
                if (maxEdge[u][i] > bestW) {
                    bestW = maxEdge[u][i];
                    bestNode = nodeMax[u][i];
                }
                u = up[u][i];
            }
        }

        if (u == v)
            return Edge{bestNode, up[bestNode][0], bestW};

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                if (maxEdge[u][i] > bestW) {
                    bestW = maxEdge[u][i];
                    bestNode = nodeMax[u][i];
                }
                if (maxEdge[v][i] > bestW) {
                    bestW = maxEdge[v][i];
                    bestNode = nodeMax[v][i];
                }
                u = up[u][i];
                v = up[v][i];
            }
        }

        if (maxEdge[u][0] > bestW) {
            bestW = maxEdge[u][0];
            bestNode = nodeMax[u][0];
        }
        if (maxEdge[v][0] > bestW) {
            bestW = maxEdge[v][0];
            bestNode = nodeMax[v][0];
        }

        return Edge{bestNode, up[bestNode][0], bestW};
    }




};
