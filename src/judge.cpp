#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>
#include "config.hpp"
using namespace std;


// ================= RUN SOLVER =============
void run_solver(const string& solver,
                Stats& stats,
                chrono::high_resolution_clock::time_point globalStart) {

    pid_t pid = fork();

    if (pid == 0) {
        // CPU limit
        rlimit cpu;
        cpu.rlim_cur = cpu.rlim_max = (rlim_t)(TIME_LIMIT + 1);
        setrlimit(RLIMIT_CPU, &cpu);

        // Memory limit
        rlimit mem;
        mem.rlim_cur = mem.rlim_max = MEM_LIMIT;
        setrlimit(RLIMIT_AS, &mem);

        freopen("input.tmp", "r", stdin);
        freopen("output.tmp", "w", stdout);

        execl(("./" + solver).c_str(), solver.c_str(), nullptr);
        exit(1); // si execl falla
    }

    int status = 0;
    bool tle = false;

    while (true) {
        pid_t r = waitpid(pid, &status, WNOHANG);
        if (r == pid) break;

        auto now = chrono::high_resolution_clock::now();
        double elapsed =
            chrono::duration<double>(now - globalStart).count();

        if (elapsed > TIME_LIMIT) {
            kill(pid, SIGKILL);
            tle = true;
            break;
        }
    }

    if (tle) {
        stats.tle++;
    }
    else if (WIFSIGNALED(status)) {
        int sig = WTERMSIG(status);
        if (sig == SIGSEGV || sig == SIGABRT || sig == SIGKILL)
            stats.mle++;
        else
            stats.re++;
    }
    else if (WEXITSTATUS(status) != 0) {
        stats.re++;
    }
    else {
        stats.ok++;
    }
}

// ================= MAIN ===================
int main() {
    ifstream in("tests.txt");
    ofstream out("results.txt");

    if (!in) {
        cerr << "❌ Error: tests.txt not found\n";
        return 1;
    }

    int T;
    in >> T;

    Stats bruteStats;
    Stats heuristicStats;

    for (int tc = 1; tc <= T; tc++) {

        // ===== Guardar caso en input.tmp =====
        ofstream tmp("input.tmp");

        int n, m;
        in >> n >> m;
        tmp << n << " " << m << "\n";

        for (int i = 0; i < m; i++) {
            int u, v, c;
            in >> u >> v >> c;
            tmp << u << " " << v << " " << c << "\n";
        }

        for (int i = 0; i < n; i++) {
            int d;
            in >> d;
            tmp << d << (i + 1 < n ? ' ' : '\n');
        }
        tmp.close();

        auto start = chrono::high_resolution_clock::now();

        // ===== Ejecutar métodos =====
        run_solver("brute", bruteStats, start);
        run_solver("heuristic", heuristicStats, start);
    }

    // ============ RESULTADOS ============
    out << "# Results of DAA – Degree Constrained MST\n\n";
    out << "| Method     | 👌 | 💥 | ⏰ | 🧠 | Final |\n";
    out << "|----------- |----|----|----|----|-------|\n";

    auto print_row = [&](const string& name, Stats& s) {
        string final =
            (s.re == 0 && s.tle == 0 && s.mle == 0) ? "✅" : "❌";

        out << "| " << setw(9) << name << " | "
            << s.ok << " | "
            << s.re << " | "
            << s.tle << " | "
            << s.mle << " | "
            << final << " |\n";
    };

    print_row("Brute", bruteStats);
    print_row("Heuristic", heuristicStats);

    out.close();
    return 0;
}
