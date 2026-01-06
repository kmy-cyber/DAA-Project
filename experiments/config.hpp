#pragma once
#include<string>
#include <iostream>
#include <fstream>

struct Config {
    int memory_limit_kb;
    int time_limit_ms;
};


Config loadConfig(const std::string& config_file) {
    Config cfg;
    
    // Valores por defecto
    cfg.memory_limit_kb = 512 * 1024;
    cfg.time_limit_ms = 5000;
    
    
    std::ifstream file(config_file);
    if (!file.is_open()) {
        std::cerr << "[WARNING] Config file not found: " << config_file << "\n";
        std::cerr << "[INFO] Using default values\n";
        return cfg;
    }
    
    std::string line;
    while (getline(file, line)) {
        // Ignorar líneas vacías y comentarios
        if (line.empty() || line[0] == '#') continue;
        
        // Encontrar el signo '='
        size_t pos = line.find('=');
        if (pos == std::string::npos) continue;
        
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        
        // Remover espacios en blanco
        key.erase(key.find_last_not_of(" \t") + 1);
        key.erase(0, key.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        
        // Mapear configuración
        if (key == "MEMORY_LIMIT_MB") {
            cfg.memory_limit_kb = stoi(value) * 1024;
        } else if (key == "TIME_LIMIT_MS") {
            cfg.time_limit_ms = stoi(value);
        } 
    }
    
    file.close();
    
    std::cout << "[CONFIG] Memory limit: " << (cfg.memory_limit_kb / 1024) << " MB\n";
    std::cout << "[CONFIG] Time limit: " << cfg.time_limit_ms << " ms\n";
    
    return cfg;
}