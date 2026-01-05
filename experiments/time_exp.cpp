#include <bits/stdc++.h>
using namespace std;

static constexpr double TIME_LIMIT_MS = 5000.0;

struct Algorithm {
    string name;
    string exec;
};

int main() {
    (void)system("mkdir -p experiments results");

    vector<int> Ns = {
        5, 10, 15, 20, 25, 30,
        60, 120, 240, 480, 960,
        1920, 3840, 7680, 15360
    };
    
    vector<Algorithm> algorithms = {
        {"brute", "./src/bin/brute"},
        {"dcmst", "./src/bin/dcmst"},
        {"lagrange", "./src/bin/lagrange"}
    };

    for (const auto& alg : algorithms) {
        string csv_name = "results/scalability/" + alg.name + "_scalability.csv";
        ofstream csv(csv_name);
        csv << "n,time_ms,status\n";

        cout << "\n=== Running " << alg.name << " ===\n";

        for (int n : Ns) {
            string test = "experiments/test.in";

            // Generar instancia
            string gen_cmd =
                "./experiments/test_generator " + to_string(n) + " > " + test;

            if (system(gen_cmd.c_str()) != 0) {
                cerr << "Error generating test for n=" << n << "\n";
                break;
            }

            // Ejecutar algoritmo
            auto start = chrono::high_resolution_clock::now();
            int ret = system((alg.exec + " " + test + " > /dev/null").c_str());
            auto end = chrono::high_resolution_clock::now();

            double t_ms =
                chrono::duration<double, milli>(end - start).count();

            string status;
            if (ret != 0)
                status = "RE";
            else if (t_ms > TIME_LIMIT_MS)
                status = "TLE";
            else
                status = "OK";

            csv << n << "," << fixed << setprecision(3)
                << t_ms << "," << status << "\n";

            cout << "n=" << n << " → "
                 << t_ms << " ms (" << status << ")\n";

            if (t_ms > TIME_LIMIT_MS)
                break;
        }

        csv.close();
    }
}
