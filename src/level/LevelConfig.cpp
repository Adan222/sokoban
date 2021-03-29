#include "LevelConfig.hpp"
#include <SFML/System/Vector2.hpp>
#include <exception>
#include <filesystem>
#include <string>
#include <vector>

LevelConfig::LevelConfig(const std::filesystem::path& fileConfigPath) : m_newConfigPath(false) {
    using json = nlohmann::json;
    using std::cout;
    std::ifstream m_levelConfigStream;
    
    m_jsonPath = "";


    try {
        //Check if file exist
        if(!std::filesystem::exists(fileConfigPath))
            throw std::runtime_error(fileConfigPath.generic_string() + " don`t exist");

        m_levelConfigStream.open(fileConfigPath);

        //Check for errors
        if(m_levelConfigStream.fail())
            throw std::runtime_error(fileConfigPath.generic_string() + ": " + std::strerror(errno));

        //can throw parsing error, thats why we are using try catch
        m_levelConfigJson = json::parse(m_levelConfigStream);
        m_jsonPath = fileConfigPath;
    } 
    catch(std::exception &e){
        
        cout << e.what() << "\n";
        exit(1);
    }

}

LevelConfig::LevelConfig() : m_newConfigPath(false) {   
    m_levelConfigJson = R"(
    {
        "map" : {
            "name" : "Default",
            "tile_atlas" : {
                "path" : "res/graphics/iso-64x64-outside.png",
                "tile_size": 64
            },
            "visual_grid" : [],
            "logic_grid" : [],  
            "theme_song" : "res/sounds/level/level_1.wav"
        }
    }
    )"_json;
    
    m_jsonPath = "";
    //references are not working, nlohmann recommends not writing to pointer/reference
    //if(validateJSON(m_levelConfigJSON)) {
       //m_mapConfigJSON = m_levelConfigJSON.at("map").get_ref<json::object_t&>();
        //m_tileAtlasJSON = m_levelConfigJSON.at("map").at("tile_atlas").get_ref<json::object_t&>();
    //}

}

LevelConfig::~LevelConfig() {}


uint32_t LevelConfig::getMapTilesAmount() const {
    uint32_t cols = WINDOW_WIDTH / getTileSize();
    uint32_t rows = WINDOW_HEIGHT / getTileSize();
    return cols * rows;
}


uint32_t LevelConfig::getMapColumns() const {
    return WINDOW_WIDTH / getTileSize();
}

std::string LevelConfig::getMapName() const {
    return m_levelConfigJson.at("map").at("name"); 
}

uint32_t LevelConfig::getTileSize() const {
    return m_levelConfigJson.at("map").at("tile_atlas").at("tile_size");
}

std::filesystem::path LevelConfig::getTileAtlasPath()  {
    //std::string is required here, otherwise, mingw throws error
    return m_levelConfigJson.at("map").at("tile_atlas").at("path").get<std::string>();
}

std::filesystem::path& LevelConfig::getJsonFilePath() {
    return m_jsonPath;
}

std::filesystem::path LevelConfig::getThemeSongPath() {
    return m_levelConfigJson.at("map").at("theme_song").get<std::string>();
}

void LevelConfig::setTileSize(const uint32_t tileSize) {
    m_levelConfigJson.at("map").at("tile_atlas").at("tile_size") = tileSize;
}

void LevelConfig::setJsonFilePath(const std::filesystem::path& openPath) {
    m_jsonPath = openPath;
    m_newConfigPath = true;
}

void LevelConfig::setTileAtlasFilePath(const std::filesystem::path& tileAtlasPath) {
    m_levelConfigJson.at("map").at("tile_atlas").at("path") = tileAtlasPath.generic_string();
}

bool LevelConfig::validateJSON(const nlohmann::json& levelConfig) {
    if(levelConfig.contains("map")) {
        auto map = levelConfig.at("map");
        if(map.contains("tile_atlas")) {
            auto tile_atlas = map.at("tile_atlas");
            if(map.contains("visual_grid") &&
                    map.contains("logic_grid") &&
                    map.contains("name") &&
                    tile_atlas.contains("path") && 
                    tile_atlas.contains("tile_size")) {
                return true;
            }
        }
    }
    return false;
}

bool LevelConfig::validateJSON(const std::filesystem::path& fileConfigPath) {
    using json = nlohmann::json;
    json levelConfig;
    
    try {
        std::ifstream m_levelConfigStream(fileConfigPath);
        levelConfig = nlohmann::json::parse(m_levelConfigStream);
    } catch(json::exception) {
        return false;
    }
    return validateJSON(levelConfig);
}



std::vector<int> LevelConfig::getVisualGrid() {
    //using [], if data is null it will create empty object
    //slow, we are copying it
    return m_levelConfigJson.at("map")["visual_grid"];
}

std::vector<int> LevelConfig::getLogicGrid() {
    //using [], if data is null it will create empty object
    //slow, we are copying it
    return m_levelConfigJson.at("map")["logic_grid"];
}

bool LevelConfig::isNewConfigPathSet() const {
    return m_newConfigPath;
}

void LevelConfig::saveLogicGrid(std::vector<int> logicGrid) {
    m_levelConfigJson.at("map").at("logic_grid") = logicGrid;
}

void LevelConfig::saveVisualGrid(std::vector<int> visualGrid) {
    m_levelConfigJson.at("map").at("visual_grid") = visualGrid;
}

void LevelConfig::saveToFile(std::filesystem::path savePath) {
    if(!savePath.is_absolute())
        savePath = std::filesystem::absolute(savePath);
    
    std::ofstream saveStream(savePath);
    saveStream << m_levelConfigJson;
    saveStream.close();
    m_jsonPath = savePath;
}

