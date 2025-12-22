#include <bits/stdc++.h>
#include "build.hpp"
using namespace std;

int main()
{
    // int n = 10;
    // Graph G(n);
    // vector<Edge> T;

    // G.addEdge(0,1,5);
    // G.addEdge(1,2,3);
    // G.addEdge(2,3,9);
    // G.addEdge(2,4,1);
    // G.addEdge(4,5,2);
    // G.addEdge(2,5,4);
    // G.addEdge(3,5,17);
    // G.addEdge(3,7,8);
    // G.addEdge(6,7,3);
    // G.addEdge(6,8,1);
    // G.addEdge(8,9,2);
    // G.addEdge(6,9,5);

    // for(int i = 0; i < n; i++)
    // {
    //     G.b[i]=2;
    // }

    // G.b[4]=G.b[5]=1;
    // G.b[2]=4;


    // Main_DCMST(G, T);

    // cout << "Edges in the DCMST:" << endl;
    // ll cost =0;

    // for(const auto& e : T) 
    // {
    //     cout << "(" << e.u << "," << e.v << "," << e.w << ")" << endl;
    //     cost += e.w;
    // }
    
    // cout << "Total cost of the DCMST: " << cost << endl;


    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    int x,y,w;

    cin >> n >> m;

    Graph G(n);
    vector<Edge> T;
    int cost =0;

    for(int i=0;i<m; i ++)
    {
        cin >> x >> y >> w ;
        G.addEdge(x,y,w);
    }

    for(int i=0;i<n;i++)
    {
        cin >> G.b[i];
    }

    Main_DCMST(G, T);

    //cout << "Edges in the DCMST:" << endl;

    for(const auto& e : T)
    {
        cost += e.w;
    }

    cout << cost << endl;
    
    for (auto &e : T)
    {
        cout << e.u << " " << e.v << " " << e.w << endl;
    }

    return 0;
}



