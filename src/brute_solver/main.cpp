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

    // Aqui va el codigo de su implementacion particular (el resto del codigo es igual)
    Main_Brute_Solver(G, T);

    IO::printSolution(T);

    return 0;
}