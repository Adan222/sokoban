#pragma once

#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

#include <nlohmann/json.hpp>

class LevelConfig {
    nlohmann::json m_levelConfig;
    std::ifstream m_levelConfigStream;
public:
    LevelConfig(const std::string& fileConfigPath);
    ~LevelConfig();
    nlohmann::json getJSON() const;
};