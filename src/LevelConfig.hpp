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
    nlohmann::json m_mapConfigJSON;
    nlohmann::json m_tileAtlasJSON;


public:
    uint32_t getMapColumns() const; //map tile columns
    uint32_t getMapTilesAmount() const; //calculate number of tiles on map, by screen res and tile size 
    std::string getMapName() const; //level name
    

    uint32_t getNumberOfTilesOnMap() const; 
    std::vector<int> getTileAtlasVisualGrid() const; 
    uint32_t getTileSize() const; //tiles size
    std::filesystem::path getTileAtlasPath() const; //path to tile atlas file

    void setTileSize(uint32_t tileSize);

    
    LevelConfig(); //generate default json if no file was provided
    LevelConfig(const std::filesystem::path& fileConfigPath);
    ~LevelConfig();
};