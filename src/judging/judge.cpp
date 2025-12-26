#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

struct Stat {
    string test;
    string status;
    double time_ms;
    int memory; // KB
};

int main() {
    vector<string> algos = {
        "bin/brute",
        "bin/dcmst"
    };
    (void) system("mkdir -p outputs logs");

    vector<fs::path> tests;
    for (const auto &e : fs::directory_iterator("tests"))
        if (e.path().extension() == ".in")
            tests.push_back(e.path());
    sort(tests.begin(), tests.end());

    for (auto &alg : algos) {
        string name = fs::path(alg).filename().string();
        cout << "== Running " << name << " ==\n";

        ofstream log_file("logs/" + name + ".csv");
        log_file << "Test,Status,Time(ms),Memory(KB)\n";

        for (auto &test_path : tests) {
            string base = test_path.stem().string();
            string out = "outputs/" + name + "_" + base + ".out";
            string tmp = "outputs/tmp_time.txt";

            string cmd = "/usr/bin/time -f \"%M %e\" " +
                         alg + " " + test_path.string() + " " + out +
                         " 2> " + tmp;

            int ret = system(cmd.c_str());

            string status;
            if (ret != 0) {
                status = "RE";
            } else {
                ret = system(("./checker " + test_path.string() + " " + out +
                              " > /dev/null 2>&1").c_str());
                status = (ret == 0 ? "OK" : "WA");
            }

            int mem = 0;
            double t_sec = 0;
            ifstream f(tmp);
            if (!(f >> mem >> t_sec)) {
                mem = 0;
                t_sec = 0;
            }

            double t_ms = t_sec * 1000.0;

            log_file << base << "," << status << ","
                     << fixed << setprecision(3)
                     << t_ms << "," << mem << "\n";
        }

        log_file.close();
    }
}
