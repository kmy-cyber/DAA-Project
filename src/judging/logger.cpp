// #include "logger.hpp"

// Logger::Logger(const string& filename) {
//     log.open(filename);
// }

// Logger::~Logger() {
//     log.close();
// }

// void Logger::logCaseHeader(int tc) {
//     log << Color::BOLD << Color::CYAN
//         << "\n================ CASE " << tc << " ================\n"
//         << Color::RESET;
// }

// void Logger::logSolverResult(const SolverLog& r, long long bestCost) {
//     string color;

//     if (!r.ok) color = Color::RED;
//     else if (r.cost == bestCost) color = Color::GREEN;
//     else color = Color::YELLOW;

//     log << color
//         << setw(12) << r.name << " | ";

//     if (!r.ok)
//         log << "INVALID\n";
//     else
//         log << "cost = " << r.cost << "\n";

//     log << Color::RESET;
// }
