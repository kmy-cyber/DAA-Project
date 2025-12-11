#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<ii> vii;

//----------------------------------------------------------------------

//----------------------------------------------------------------------

//----------------------------------------------------------------------

//----------------------------------------------------------------------

//----------------------------------------------------------------------

//----------------------------------------------------------------------

//----------------------------------------------------------------------

//----------------------------------------------------------------------

// bool degreeConstrainedTree(int n, vvi & g, int k) {
//     vi deg(n, 0);
//     vector<bool> vis(n, false);
//     vii tree;

//     queue<int> q;
//     q.push(0);
//     vis[0] = true;

//     while (!q.empty()) {
//         int u = q.front(); q.pop();

//         for (int v : g[u]) {
//             if (!vis[v]) {

//                 if (deg[u] >= k || deg[v] >= k)
//                     continue;

//                 // add edge
//                 tree.emplace_back(u, v);
//                 deg[u]++; deg[v]++;
//                 vis[v] = true;
//                 q.push(v);

//                 if ((int)tree.size() == n-1)
//                     return true;
//             }
//         }
//     }

//     return false;
// }

// int main() {

//     int n, m, k;
//     cin >> n >> m >> k;

//     vvi g(n);
//     for (int i = 0; i < m; i++) {
//         int u, v;
//         cin >> u >> v;
//         g[u].push_back(v);
//         g[v].push_back(u);
//     }

//     bool ok = degreeConstrainedTree(n, g, k);

//     if (ok) cout << "Se encontro un arbol abarcador con grados <= " << k << endl;
//     else cout << "No se pudo construir" << endl;

//     return 0;
// }

bool degreeConstrainedTree(int n, vector<vii>& g)
{
    
    return 1;
}

int main()
{
    // n: numero de vertices
    // m: numero de aristas de las que se conocen el costo
    int n, m;
    cin >> n >> m;

    vector<vii> g(n);

    for(int i=0;i<m;i++)
    {
        // <u,v> arista y c su costo
        int u,v,c;
        cin >> u >> v >> c;
        g[u].push_back({v,c});
        g[v].push_back({u,c});
    }

    bool ok = degreeConstrainedTree(n,g);


    return 0;
}
