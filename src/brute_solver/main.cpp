// #include <bits/stdc++.h>
// #include "brute_solver.hpp"
// using namespace std;

// int main()
// {
//     // n: numero de vertices
//     // m: numero de aristas
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
    
//     int n,m;
//     cin >> n>> m;

//     vEdges edges(m);

//     for(int i=0;i< m; i++)
//     {
//         // arista y el costo
//         cin >> edges[i].u >> edges[i].v >> edges[i].w;
//     }

//     vi maxDeg(n);
//     for(int i=0;i<n;i++)
//     {
//         // grado maximo de cada vertice
//         cin >> maxDeg[i];
//     }

//     auto[bestCost, tree] = degreeConstrainedMST(n,edges,maxDeg);

//     if(bestCost == LONG_MAX)
//     {
//         cout << "-1" << endl;
//         return 0;
//     }

//     cout << bestCost << endl;

//     for (auto &e : tree)
//     {
//         cout << e.u << " " << e.v << " " << e.w << endl;
//     }

//     return 0;
// }


#include "../utils/io.hpp" 
#include "brute_solver.hpp"
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc > 1) {
        if (!freopen(argv[1], "r", stdin)) {
            perror("freopen input failed");
            return 1;
        }
    }

    if (argc > 2) {
        if (!freopen(argv[2], "w", stdout)) {
            perror("freopen output failed");
            return 1;
        }
    }

    Graph G = IO::readGraphFromStdin();
    vector<Edge> T;

    Main_Brute_Solver(G, T);

    IO::printSolution(T);

    return 0;
}