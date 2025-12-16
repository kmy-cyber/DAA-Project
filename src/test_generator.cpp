#include <bits/stdc++.h>
using namespace std;

struct Edge { int u,v,c; };

int rnd(mt19937 &rng, int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int main() {
    const int SEED = 123456;   // 🔒 semilla fija
    mt19937 rng(SEED);

    ofstream out("tests.txt");

    int T = 20;   // número de casos
    out << T << "\n";

    for (int tc = 1; tc <= T; tc++) {
        int n = rnd(rng, 5, 12);
        int extra = rnd(rng, 0, n);
        int maxCost = 100;

        vector<Edge> edges;

        // Árbol base
        for (int i = 1; i < n; i++) {
            int p = rnd(rng, 0, i - 1);
            edges.push_back({p, i, rnd(rng, 1, maxCost)});
        }

        set<pair<int,int>> used;
        for (auto &e : edges) {
            used.insert({min(e.u,e.v), max(e.u,e.v)});
        }

        // Aristas extra
        while ((int)edges.size() < n - 1 + extra) {
            int u = rnd(rng, 0, n - 1);
            int v = rnd(rng, 0, n - 1);
            if (u == v) continue;
            auto p = make_pair(min(u,v), max(u,v));
            if (used.count(p)) continue;
            used.insert(p);
            edges.push_back({u, v, rnd(rng, 1, maxCost)});
        }

        vector<int> maxDeg(n);
        for (int i = 0; i < n; i++)
            maxDeg[i] = rnd(rng, 1, min(4, n-1));

        // output caso
        out << n << " " << edges.size() << "\n";
        for (auto &e : edges)
            out << e.u << " " << e.v << " " << e.c << "\n";
        for (int i = 0; i < n; i++)
            out << maxDeg[i] << (i+1<n?' ':'\n');
    }

    out.close();
    return 0;
}
