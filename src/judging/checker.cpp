#include <bits/stdc++.h>
#include "../utils/dsu.hpp"
using namespace std;

int main(int argc, char** argv) {

    if (argc != 3) {
        cerr << "Usage: checker input.txt output.txt\n";
        return 1;
    }

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if (!in || !out) {
        cerr << "Cannot open files\n";
        return 1;
    }

    /* ---------- Leer input ---------- */
    int n, m;
    in >> n >> m;

    // Guardamos las aristas válidas
    map<pair<int,int>, int> edgeWeight;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        in >> u >> v >> w;
        if (u > v) swap(u, v);
        edgeWeight[{u, v}] = w;
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++)
        in >> b[i];

    /* ---------- Leer output ---------- */
    long long claimed_cost;
    if (!(out >> claimed_cost)) {
        cerr << "No cost printed\n";
        return 1;
    }


    if (claimed_cost == -1) {
        
        string extra;
        if (out >> extra) {
            cerr << "Extra output after -1\n";
            return 1;
        }
        cout << "OK\n";
        return 0;
    }

    vector<tuple<int,int,int>> T;
    int u, v, w;
    while (out >> u >> v >> w) {
        T.emplace_back(u, v, w);
    }

    /* ---------- Verificar tamaño ---------- */
    if ((int)T.size() != n - 1) {
        cerr << "Invalid number of edges (not a tree)\n";
        return 1;
    }

    /* ---------- Verificar árbol ---------- */
    DSU dsu(n);
    vector<int> degree(n, 0);
    long long real_cost = 0;

    for (auto &[x, y, z] : T) {
        int a = x, b2 = y;
        if (a > b2) swap(a, b2);

        if (!edgeWeight.count({a, b2})) {
            cerr << "Edge does not exist in input\n";
            return 1;
        }

        if (edgeWeight[{a, b2}] != z) {
            cerr << "Incorrect edge weight\n";
            return 1;
        }

        if (!dsu.merge(x, y)) {
            cerr << "Cycle detected\n";
            return 1;
        }

        degree[x]++;
        degree[y]++;
        real_cost += z;
    }

    /* ---------- Verificar conectividad ---------- */
    int root = dsu.find(0);
    for (int i = 1; i < n; i++) {
        if (dsu.find(i) != root) {
            cerr << "Graph is not connected\n";
            return 1;
        }
    }

    /* ---------- Restricción de ETECSA ---------- */
    for (int i = 0; i < n; i++) {
        if (degree[i] > b[i]) {
            cerr << "Degree constraint violated at node " << i << "\n";
            return 1;
        }
    }

    /* ---------- Verificar costo ---------- */
    if (real_cost != claimed_cost) {
        cerr << "Cost mismatch\n";
        return 1;
    }

    cout << "OK\n";
    return 0;
}
