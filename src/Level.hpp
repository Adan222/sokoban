#pragma once
#include <string>
#include <fstream>
#include <stdexcept>
#include <../vendor/nlohmann/include/json.hpp>



using json = nlohmann::json;

class Level {
std::ifstream m_levelConfigStream;
public:
    Level(const std::string& filename);
    ~Level();
};