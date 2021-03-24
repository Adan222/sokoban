#include "LevelConfig.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <string>
#include <vector>

LevelConfig::LevelConfig(const std::filesystem::path& fileConfigPath){
    using json = nlohmann::json;
    using std::cout;

    try {
        //Check if file exist
        if(!std::filesystem::exists(fileConfigPath))
            throw std::runtime_error(fileConfigPath.generic_string() + " don`t exist");

        m_jsonPath = fileConfigPath;
        m_levelConfigStream.open(fileConfigPath);

        //Check for errors
        if(m_levelConfigStream.fail())
            throw std::runtime_error(fileConfigPath.generic_string() + ": " + std::strerror(errno));

        //can throw parsing error, thats why we are using try catch
        m_levelConfigJSON = json::parse(m_levelConfigStream);

        //TO DO: maybe wrap in function, do error checking?
        m_mapConfigJSON = m_levelConfigJSON.at("map").get_ref<json::object_t&>();
        m_tileAtlasJSON = m_mapConfigJSON.at("tile_atlas").get_ref<json::object_t&>();
    } 
    catch(std::exception &e){
        cout << e.what() << "\n";
        exit(1);
    }

}

LevelConfig::LevelConfig() {
    using json = nlohmann::json;
    try{
        m_levelConfigJSON = R"(
        {
            "map" : {
                "name" : "Default",
                "tile_atlas" : {
                    "path" : "iso-64x64-outside.png",
                    "tile_size": 64
                },
                "visual_grid" : [1, 2, 3, 3],
                "logical_grid" : [0, 0, 1, 2],
                
                "zoom" : 1.0
            }
        }
        )"_json;
        
        m_mapConfigJSON = m_levelConfigJSON.at("map").get_ref<json::object_t&>();
        
        m_tileAtlasJSON = m_mapConfigJSON.at("tile_atlas").get_ref<json::object_t&>();
    } catch(std::exception &e){
        std::cout << e.what() << "\n";
        exit(1);
    }
    
    
}

uint32_t LevelConfig::getMapTilesAmount() const {
    //we assume that screen res is 1024 x 768
    uint32_t cols = 1024 / getTileSize();
    uint32_t rows = 768 / getTileSize();
   
    return cols * rows;
}


uint32_t LevelConfig::getMapColumns() const {
    return 1024 / getTileSize();
}

std::string LevelConfig::getMapName() const {
    return m_mapConfigJSON.at("name"); 
}

uint32_t LevelConfig::getTileSize() const {
    return m_tileAtlasJSON.at("tile_size");
}

std::filesystem::path LevelConfig::getTileAtlasPath() const {
    return m_tileAtlasJSON.at("path").get<std::string>();
}

void LevelConfig::setTileSize(uint32_t tileSize) {
    m_tileAtlasJSON.at("tile_size") = tileSize;
}

Grid LevelConfig::getTileAtlasVisualGrid() const {
    if(m_mapConfigJSON.contains("visual_grid")) { 
        return m_mapConfigJSON["visual_grid"];
    } else {
        throw std::runtime_error("There is no visual grid object in: " + m_jsonPath.generic_string());
    }

    //TO DO we shouldnt test it in getters/setters, we should test those when reading file
}

Grid LevelConfig::getTileAtlasLogicalGrid() const{
    if(m_mapConfigJSON.contains("logical_grid")) {
        return m_mapConfigJSON["logical_grid"];
    } else {
        throw std::runtime_error("There is no logic grid object in: " + m_jsonPath.generic_string());
    }
    //TO DO we shouldnt test it in getters/setters, we should test those when reading file

}

LevelConfig::~LevelConfig() {
    m_levelConfigStream.close();
}

void LevelConfig::selfTest() const{
    getMapColumns();
    getMapTilesAmount();
    getMapName();
    
    getTileSize();
    getTileAtlasPath();
    getTileAtlasVisualGrid();
    getTileAtlasLogicalGrid();
    
}