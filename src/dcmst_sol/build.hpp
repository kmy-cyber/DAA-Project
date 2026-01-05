#pragma once
#include <vector>
#include <algorithm>
#include <numeric> 
#include <climits>
#include "../utils/graph.hpp"
#include "../utils/dsu.hpp"
#include "reduction.hpp"
#include "heuristic.hpp"
#include "optexchange.hpp"


void buildDegreeConstrainedMST(Graph& G, vEdges& T) {
    // Ordenar aristas por peso
    vEdges sortedEdges = G.edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(),
              [](const Edge& a, const Edge& b) { return a.w < b.w; });

    // std::cout << "buildDegreeConstrainedMST" << std::endl;

    // for(const auto&v : sortedEdges)
    // {
    //     std::cout << v.u << " " << v.v << " " << v.w << std::endl;
    // }

    DSU dsu(G.n);
    vi degT(G.n, 0);

    for(const auto& v : T)
    {
        dsu.merge(v.u,v.v);
        degT[v.u]++;
        degT[v.v]++;
    }

    // for(const auto& v : degT) std::cout << v <<  " " ;

    // std::cout << std::endl;

    // for(int i=0;i<dsu.parent.size();i++) std::cout << dsu.parent[i] << " ";

    // std::cout << std::endl;

    for(const auto& e : sortedEdges)
    {
        if(dsu.find(e.u) != dsu.find(e.v) && degT[e.u] < G.b[e.u] && degT[e.v] < G.b[e.v])
        {
            T.push_back({e.u,e.v,e.w});
            G.removeEdge(e.u,e.v);
            dsu.merge(e.u,e.v);
            degT[e.u]++;
            degT[e.v]++;
        }

        if((int)T.size() == G.n - 1) break;
    }

}



void Main_DCMST(Graph& G,vEdges& T) {
    
    if(!Reduction_DCMST(G,T)) {T.clear(); return;}

    // std::cout << "Initial T: " << std::endl;
    // for(const auto& v : T)
    // {
    //     std::cout << v.u << " " << v.v << std::endl;
    // }

    // std::cout << "End T of Reduction: " << std::endl;


    // std::cout << "Initial G: " << std::endl;
    // for(const auto& v : G.edges)
    // {
    //     std::cout << v.u << " " << v.v << std::endl;
    // }

    // std::cout << "End G of Reduction: " << std::endl;
    
    buildDegreeConstrainedMST(G, T);

    // std::cout << "Build Degree T: " << std::endl;

    // for(const auto& v : T)
    // {
    //     std::cout << v.u << " " << v.v << std::endl;
    // }

    // std::cout << "End T of buildDegree: " << std::endl;


    // G.printGraph();


    // comprobar que T sea un arbol
    // if((int)T.size() != G.n -1) T.clear();

    // while((int)T.size() < G.n -1)
    // {
    //     if(!connectComponentsHeuristicAdvanced(G,T)) break;
    // }

    // if ((int)T.size() != G.n - 1) {
    //     T.clear();
    //     return;
    // }

    if((int)T.size() < G.n -1)
        connectComponentsHeuristicAdvanced(G,T);

    if ((int)T.size() != G.n - 1) {
        T.clear();
        return;
    }

    // std::cout << "Second G: " << std::endl;
    // for(const auto& v : G.edges)
    // {
    //     std::cout << v.u << " " << v.v << std::endl;
    // }

    // std::cout << "End G of Heuristic: " << std::endl;

    oneOptExchange(G, T);

   // G.printGraph();

    // twoOptExchange(G, T);

}
