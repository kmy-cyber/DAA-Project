#include <bits/stdc++.h>
#include "edge.hpp"
#include "dsu.hpp"
using namespace std;

/* ==========================
   Kernelization
   ========================== */
vector<Edge> kernelize(
    int n,
    const vector<Edge>& edges,
    const vector<int>& deg_limit
) {
    vector<vector<Edge>> adj(n);

    for (auto &e : edges) {
        if (deg_limit[e.u] > 0 && deg_limit[e.v] > 0) {
            adj[e.u].push_back(e);
            adj[e.v].push_back({e.v, e.u, e.c});
        }
    }

    int maxD = *max_element(deg_limit.begin(), deg_limit.end());
    int K = max(2, 2 * maxD);

    vector<Edge> kernel;

    for (int u = 0; u < n; u++) {
        auto &v = adj[u];
        sort(v.begin(), v.end(),
             [](auto &a, auto &b) { return a.c < b.c; });

        for (int i = 0; i < (int)v.size() && i < K; i++) {
            if (u < v[i].v) kernel.push_back(v[i]);
        }
    }

    return kernel;
}

/* ==========================
   Kernel MST Heuristic
   ========================== */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].c;

    vector<int> deg_limit(n);
    for (int i = 0; i < n; i++)
        cin >> deg_limit[i];

    /* ==========================
       Kernelization step
       ========================== */
    vector<Edge> kernel = kernelize(n, edges, deg_limit);

    sort(kernel.begin(), kernel.end(),
         [](auto &a, auto &b) { return a.c < b.c; });

    DSU dsu(n);
    vector<int> deg(n, 0);
    vector<Edge> result;

    /* ==========================
       Kruskal with degree bounds
       ========================== */
    for (auto &e : kernel) {
        if ((int)result.size() == n - 1) break;

        if (dsu.find(e.u) == dsu.find(e.v)) continue;
        if (deg[e.u] + 1 > deg_limit[e.u]) continue;
        if (deg[e.v] + 1 > deg_limit[e.v]) continue;

        dsu.merge(e.u, e.v);
        deg[e.u]++;
        deg[e.v]++;
        result.push_back(e);
    }

    /* ==========================
       Output
       ========================== */
    long long total_cost = 0;
    for (auto &e : result)
        total_cost += e.c;

    cout << total_cost << "\n";
    for (auto &e : result)
        cout << e.u << " " << e.v << " " << e.c << "\n";

    return 0;
}
