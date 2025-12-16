#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>
using namespace std;

// ⏱️ Tiempo máximo por caso
const double TIME_LIMIT = 10.0; // segundos

// 🧠 Memoria máxima por ejecución
const long long MEM_LIMIT = 512LL * 1024 * 1024; // 512 MB

int main() {
    ifstream in("tests.txt");
    ofstream out("results.txt");

    int T;
    in >> T;

    out << "Case | Result | Time\n";
    out << "----------------------\n";

    for (int tc = 1; tc <= T; tc++) {
        /* ===============================
           Guardar caso actual en input.tmp
           =============================== */
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

        /* ===============================
           PROCESO HIJO → ejecutar solver
           =============================== */
        if (pid == 0) {
            // ⏱️ Límite de CPU (backup del timer externo)
            rlimit cpu;
            cpu.rlim_cur = cpu.rlim_max = (rlim_t)(TIME_LIMIT + 1);
            setrlimit(RLIMIT_CPU, &cpu);

            // 🧠 Límite de memoria virtual
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
            exit(1); // si execl falla
        }

        /* ===============================
           PROCESO PADRE → juez
           =============================== */
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

        auto end = chrono::high_resolution_clock::now();
        double elapsed =
            chrono::duration<double>(end - start).count();

        /* ===============================
           Decidir resultado
           =============================== */
        string result;

        if (tle) {
            result = "⏱️";
        }
        else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);

            if (sig == SIGKILL || sig == SIGSEGV || sig == SIGABRT) {
                result = "🧠";  // Memory limit / stack overflow
            } else {
                result = "💥";  // Runtime error
            }
        }
        else if (WEXITSTATUS(status) != 0) {
            result = "💥";
        }
        else {
            // aquí luego puedes meter checker vs brute
            result = "✅";
        }

        out << setw(4) << tc << " | " << result
            << " | " << fixed << setprecision(3)
            << elapsed << "s\n";
    }

    out.close();
    return 0;
}
