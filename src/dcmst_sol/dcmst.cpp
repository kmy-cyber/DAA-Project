#include "../utils/io.hpp" 
#include "build.hpp"
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

    Main_DCMST(G, T);

    IO::printSolution(T);

    return 0;
}


