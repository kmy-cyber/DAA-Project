#include <bits/stdc++.h>
using namespace std;

static constexpr int MEMORY_LIMIT_KB = 512 * 1024; // 512 MB

struct Algorithm {
    string name;
    string exec;
};

int main() {
    system("mkdir -p experiments results tmp");

    /* Tamaños base */
    vector<int> Ns_base = {5, 10, 15, 20, 25, 30, 60, 120, 240, 480, 960};

    vector<Algorithm> algorithms = {
        {"brute", "./src/bin/brute"},
        {"dcmst", "./src/bin/dcmst"},
        {"lagrange", "./src/bin/lagrange"}
    };

    for (const auto& alg : algorithms) {
        cout << "\n=== Memory test: " << alg.name << " ===\n";

        string csv_name = "results/memory/" + alg.name + "_memory.csv";
        ofstream csv(csv_name);
        csv << "n,memory_kb,status\n";

        bool stop = false;
        int last_ok_n = -1;

        /* ===== Fase 1: tamaños base ===== */
        for (int n : Ns_base) {
            string test = "experiments/test.in";
            string memlog = "tmp/mem.txt";

            /* Generar instancia */
            string gen_cmd =
                "./experiments/test_generator " + to_string(n) + " > " + test;
            if (system(gen_cmd.c_str()) != 0) break;

            /* Ejecutar y medir memoria */
            string cmd =
                "/usr/bin/time -f \"%M\" " + alg.exec + " " + test +
                " > /dev/null 2> " + memlog;

            system(cmd.c_str());

            int mem_kb = 0;
            ifstream mf(memlog);
            mf >> mem_kb;

            string status = (mem_kb > MEMORY_LIMIT_KB) ? "MLE" : "OK";

            csv << n << "," << mem_kb << "," << status << "\n";
            cout << "n=" << n << " → " << mem_kb << " KB (" << status << ")\n";

            if (status != "OK") {
                stop = true;
                break;
            }

            last_ok_n = n;
        }

        /* ===== Fase 2: duplicación exponencial ===== */
        if (!stop && last_ok_n > 0) {
            int n = last_ok_n * 2;

            while (true) {
                string test = "experiments/test.in";
                string memlog = "tmp/mem.txt";

                string gen_cmd =
                    "./experiments/test_generator " + to_string(n) + " > " + test;
                if (system(gen_cmd.c_str()) != 0) break;

                string cmd =
                    "/usr/bin/time -f \"%M\" " + alg.exec + " " + test +
                    " > /dev/null 2> " + memlog;

                system(cmd.c_str());

                int mem_kb = 0;
                ifstream mf(memlog);
                mf >> mem_kb;

                string status = (mem_kb > MEMORY_LIMIT_KB) ? "MLE" : "OK";

                csv << n << "," << mem_kb << "," << status << "\n";
                cout << "n=" << n << " → " << mem_kb << " KB (" << status << ")\n";

                if (status != "OK")
                    break;

                n *= 2;  // X, 2X, 4X, 8X, ...
            }
        }

        csv.close();
    }

    cout << "\nMemory scalability experiments finished.\n";
}
