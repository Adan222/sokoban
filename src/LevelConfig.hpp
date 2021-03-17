#pragma once

#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <filesystem>

#include <nlohmann/json.hpp>

class LevelConfig {
    std::ifstream m_levelConfigStream;
    
    nlohmann::json m_levelConfigJSON;
    nlohmann::json mapConfigJSON;
    nlohmann::json tileAtlasJSON;
public:
    uint32_t getMapWidth() const; //map tile columns
    std::string getMapName() const; //level name
    
    std::vector<uint16_t> getTileAtlasVisualGrid() const; 
    uint32_t getTileAtlasTileSize() const; //tiles size
    uint32_t getTileAtlasColumns() const; //amount of columns in atlas file
    std::filesystem::path getTileAtlasPath() const; //path to tile atlas file
    
    LevelConfig(const std::filesystem::path& fileConfigPath);
    ~LevelConfig();
};