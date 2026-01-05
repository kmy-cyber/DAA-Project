#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

static constexpr double TIME_LIMIT_SEC = 5.0;
static constexpr int MEMORY_LIMIT_KB = 512 * 1024;

struct AlgoStats {
    int ok = 0;        // 👌 óptimo
    int bad = 0;       // 👎 subóptimo
    int wa = 0;        // 💥 checker fail
    int tle = 0;       // ⏰ time
    int mle = 0;       // 🧠 memory
};

bool read_cost(const string &file, double &cost) {
    ifstream f(file);
    if (!f.is_open()) return false;
    f >> cost;
    return !f.fail();
}


int main() {
    vector<string> algos = {
        "bin/brute",
        "bin/dcmst",
        "bin/lagrange"
    };

    system("mkdir -p outputs logs");

    vector<fs::path> tests;
    for (const auto &e : fs::directory_iterator("tests"))
        if (e.path().extension() == ".in")
            tests.push_back(e.path());
    sort(tests.begin(), tests.end());

    map<string, AlgoStats> summary;

    for (auto &alg : algos) {
        string name = fs::path(alg).filename().string();
        cout << "== Running " << name << " ==\n";

        ofstream log_file("logs/" + name + ".csv");
        log_file << "Test,Status,Time(ms),Memory(KB),Cost\n";

        for (auto &test_path : tests) {
            string base = test_path.stem().string();
            string out = "outputs/" + name + "_" + base + ".out";
            string tmp = "outputs/tmp_time.txt";

            string cmd = "/usr/bin/time -f \"%M %e\" " +
                         alg + " " + test_path.string() + " " + out +
                         " 2> " + tmp;

            auto start = chrono::high_resolution_clock::now();
            int ret = system(cmd.c_str());
            auto end = chrono::high_resolution_clock::now();

            double t_ms = chrono::duration<double, milli>(end - start).count();

            int mem = 0;
            ifstream mf(tmp);
            mf >> mem;

            bool tle = (t_ms > TIME_LIMIT_SEC * 1000.0);
            bool mle = (mem > MEMORY_LIMIT_KB);

            if (tle) summary[name].tle++;
            if (mle) summary[name].mle++;

            if (ret != 0) {
                summary[name].wa++;
                log_file << base << ",RE," << t_ms << "," << mem << ",-\n";
                continue;
            }

            ret = system(("bin/checker " + test_path.string() + " " + out +
                          " > /dev/null 2>&1").c_str());

            if (ret != 0) {
                summary[name].wa++;
                log_file << base << ",WA," << t_ms << "," << mem << ",-\n";
                continue;
            }

            double cost;
            if (!read_cost(out, cost)) {
                summary[name].wa++;
                continue;
            }

            log_file << base << ",OK," << fixed << setprecision(3)
                     << t_ms << "," << mem << "," << cost << "\n";
        }
        log_file.close();
    }

    /* ========= COMPARACIÓN DE COSTOS ========= */
    for (auto &test_path : tests) {
        string base = test_path.stem().string();

        double best = numeric_limits<double>::infinity();
        map<string, double> cost;

        for (auto &alg : algos) {
            string name = fs::path(alg).filename().string();
            string out = "outputs/" + name + "_" + base + ".out";
            double c;
            if (read_cost(out, c)) {
                cost[name] = c;
                if(c==-1) continue;
                best = min(best, c);
            }
        }

        double brute_cost = cost.count("brute") ? cost["brute"] : -1;

        for (auto &[name, c] : cost) {
            if(brute_cost == -1)
            {
                if(c == -1) summary[name].ok++;
                else  summary[name].bad++;
                
            }
            else if(c==-1)
            {
                summary[name].bad++;
            }

            else if (c== best)
            {
                summary[name].ok++;
            }
            else summary[name].bad++;

            
        }
    }

    /* ========= OUTPUT FINAL ========= */
    ofstream md("output.md");

    md << "| Algorithm | Result | 👌 | 👎 | 💥 | ⏰ | 🧠 |\n";
    md << "|----------|--------|----|----|----|----|----|\n";

    for (auto &alg : algos) {
        string name = fs::path(alg).filename().string();
        auto &s = summary[name];

        s.bad -= s.wa;

        bool pass = (s.bad == 0 && s.wa == 0 && s.tle == 0 && s.mle == 0);
        md << "| " << name
           << " | " << (pass ? "✅" : "❌")
           << " | " << s.ok
           << " | " << s.bad
           << " | " << s.wa
           << " | " << s.tle
           << " | " << s.mle
           << " |\n";
    }

    md.close();

    cout << "Resumen generado en output.md\n";
}
