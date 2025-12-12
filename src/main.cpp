#include <bits/stdc++.h>
#include "brute_solver.hpp"
using namespace std;

int main()
{
    int n,m;
    cin >> n>> m;

    vEdges edges(m);

    for(int i=0;i< m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].c;
    }

    vi maxDeg(n);
    for(int i=0;i<n;i++)
    {
        cin >> maxDeg[i];
    }

    auto[bestCost, tree] = degreeConstrainedMST(n,edges,maxDeg);

    if(bestCost == LONG_MAX)
    {
        cout << "-1" << endl;
        return 0;
    }

    cout << bestCost << endl;

    for (auto &e : tree)
    {
        cout << e.u << " " << e.v << " " << e.c << endl;
    }

    return 0;
}