#pragma once
#include "types.hpp"

// ⏱️ Tiempo máximo por caso
const double TIME_LIMIT = 10.0;

// 🧠 Memoria máxima
const ll MEM_LIMIT = 512LL * 1024 * 1024;

// Estadísticas acumuladas
struct Stats {
    int ok = 0;
    int wrong = 0;
    int re = 0;
    int tle = 0;
    int mle = 0;
};