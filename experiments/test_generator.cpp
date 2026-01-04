#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: test_generator n [seed]\n";
        return 1;
    }

    int n = atoi(argv[1]);
    unsigned seed = (argc > 2 ? atoi(argv[2]) : 47);
    mt19937 rng(seed);

    int m = n * (n - 1) / 2;   // casi completo

    cout << n << " " << m << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int w = 1 + rng() % 100;
            cout << i << " " << j << " " << w << "\n";
        }
    }

    // restricciones de grado (no limitan)
    for (int i = 0; i < n; i++) {
        cout << n - 1 << " ";
    }
    cout << "\n";
}
