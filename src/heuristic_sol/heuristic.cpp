#include <bits/stdc++.h>
#include "../utils/edge.hpp"
#include "../utils/dsu.hpp"
using namespace std;

/* ==========================
   Penalized cost
   ========================== */
double penalized_cost(const Edge &e,
                      const vector<int> &deg,
                      const vector<int> &lim,
                      double alpha) {
    double pu = (double)deg[e.u] / lim[e.u];
    double pv = (double)deg[e.v] / lim[e.v];
    return e.w * (1.0 + alpha * (pu + pv));
}

/* ==========================
   Heuristic solver
   ========================== */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    vector<int> deg_limit(n);
    for (int i = 0; i < n; i++)
        cin >> deg_limit[i];

    vector<int> deg(n, 0);
    DSU dsu(n);

    const double ALPHA = 1.0;

    vector<Edge> result;
    result.reserve(n - 1);

    vector<int> used(m, 0);

    /* ==========================
       Greedy construction
       ========================== */
    for (int iter = 0; iter < n - 1; iter++) {
        int best = -1;
        double best_cost = 1e18;

        for (int i = 0; i < m; i++) {
            if (used[i]) continue;

            const auto &e = edges[i];

            if (dsu.find(e.u) == dsu.find(e.v)) continue;
            if (deg[e.u] + 1 > deg_limit[e.u]) continue;
            if (deg[e.v] + 1 > deg_limit[e.v]) continue;

            double c = penalized_cost(e, deg, deg_limit, ALPHA);
            if (c < best_cost) {
                best_cost = c;
                best = i;
            }
        }

        /* ==========================
           Fallback (relajación mínima)
           ========================== */
        if (best == -1) {
            for (int i = 0; i < m; i++) {
                if (used[i]) continue;
                const auto &e = edges[i];
                if (dsu.find(e.u) == dsu.find(e.v)) continue;

                double c = penalized_cost(e, deg, deg_limit, ALPHA * 5);
                if (c < best_cost) {
                    best_cost = c;
                    best = i;
                }
            }
            if (best == -1) break; // imposible conectar
        }

        auto &e = edges[best];
        used[best] = 1;

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
        total_cost += e.w;

    cout << total_cost << "\n";
    for (auto &e : result) {
        cout << e.u << " " << e.v << " " << e.w << "\n";
    }

    return 0;
}
