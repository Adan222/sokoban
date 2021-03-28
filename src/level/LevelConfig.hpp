#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <filesystem>

#include <nlohmann/json.hpp>

const uint32_t WINDOW_WIDTH  = 1024;
const uint32_t WINDOW_HEIGHT = 768;

typedef std::vector<uint32_t> Grid;
typedef std::vector<sf::Vector2i> Positions;

class LevelConfig {
    nlohmann::json m_levelConfigJson;

    std::filesystem::path m_jsonPath;
    bool m_newConfigPath;

public:
    uint32_t getMapColumns() const; //map tile columns
    uint32_t getMapTilesAmount() const; //calculate number of tiles on map, by screen res and tile size 
    std::string getMapName() const; //level name

    uint32_t getTileSize() const; //tiles size
    std::filesystem::path  getTileAtlasPath() ; //path to tile atlas file
    std::filesystem::path& getJsonFilePath();
    std::vector<int>   getVisualGrid(); 
    std::vector<int> getLogicGrid();

    bool isNewConfigPathSet() const;
public:
    void saveLogicGrid(std::vector<int> logicGrid);
    void saveVisualGrid(std::vector<int> visualGrid);

    void saveToFile(std::filesystem::path savePath);

    void setTileSize(const uint32_t tileSize);
    void setJsonFilePath(const std::filesystem::path& openPath);
    void setTileAtlasFilePath(const std::filesystem::path& tileAtlasPath);


public:
    static bool validateJSON(const nlohmann::json& levelConfig);
    static bool validateJSON(const std::filesystem::path& fileConfigPath);

    LevelConfig(); //generate default json if no file was provided
    LevelConfig(const std::filesystem::path& fileConfigPath);
    ~LevelConfig();

};