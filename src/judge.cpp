#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>
#include "basic.hpp"
using namespace std;


int main() {
    ifstream in("tests.txt");
    ofstream out("results.txt");

    if (!in) {
        cerr << "Error: tests.txt not found\n";
        return 1;
    }

    int T;
    in >> T;

    Stats stats;

    for (int tc = 1; tc <= T; tc++) {

        // Guardar input del caso
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
        pid_t pid = fork();

        // ================= HIJO =================
        if (pid == 0) {
            rlimit cpu;
            cpu.rlim_cur = cpu.rlim_max = (rlim_t)(TIME_LIMIT + 1);
            setrlimit(RLIMIT_CPU, &cpu);

            rlimit mem;
            mem.rlim_cur = mem.rlim_max = MEM_LIMIT;
            setrlimit(RLIMIT_AS, &mem);

            if (!freopen("input.tmp", "r", stdin)) {
                perror("freopen input.tmp");
                exit(1);
            }
            if (!freopen("output.tmp", "w", stdout)) {
                perror("freopen output.tmp");
                exit(1);
            }
            execl("./main", "./main", nullptr);
            exit(1);
        }

        // ================= PADRE =================
        int status = 0;
        bool tle = false;

        while (true) {
            pid_t r = waitpid(pid, &status, WNOHANG);
            if (r == pid) break;

            auto now = chrono::high_resolution_clock::now();
            double elapsed =
                chrono::duration<double>(now - start).count();

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
            if (sig == SIGSEGV || sig == SIGKILL || sig == SIGABRT)
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

    // ================= SALIDA FINAL =================
    out << "# Results of DAA – Degree Constrained MST\n\n";
    out << "| Method             | 👌  | 👎  | 💥  | ⏰  | 🧠  | Final |\n";
    out << "| -----------------  | --- | --- | ---  | --- | ---  | ----- |\n";

    string finalResult =
        (stats.wrong == 0 && stats.re == 0 &&
         stats.tle == 0 && stats.mle == 0)
        ? "✅" : "❌";

    out << "|   Brute Force      | "
        << stats.ok << "  | "
        << stats.wrong << "   | "
        << stats.re << "    |  "
        << stats.tle << "  |  "
        << stats.mle << "   |  "
        << finalResult << "   | \n";

    out.close();
    return 0;
}
