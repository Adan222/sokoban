#include "LevelConfig.hpp"
#include <SFML/System/Vector2.hpp>
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

        m_levelConfigStream.open(fileConfigPath);

        //Check for errors
        if(m_levelConfigStream.fail())
            throw std::runtime_error(fileConfigPath.generic_string() + ": " + std::strerror(errno));

        //can throw parsing error, thats why we are using try catch
        m_levelConfigJSON = json::parse(m_levelConfigStream);

        //TO DO: maybe wrap in function, do error checking?
        m_mapConfigJSON = m_levelConfigJSON.at("map");
        m_tileAtlasJSON = m_mapConfigJSON.at("tile_atlas");

    } 
    catch(std::exception &e){
        cout << e.what() << "\n";
    }

}

uint32_t LevelConfig::getMapMaxTilesAmount() const {
    //we assume that screen res is 1024 to 768
    uint32_t cols = 1024 / getTileAtlasTileSize();
    uint32_t rows = 768 / getTileAtlasTileSize();
    if(getMapWidth() != cols)
        throw std::runtime_error("Map width provided in config is not valid for that tile size.");

    return cols * rows;
}

uint32_t LevelConfig::getTileAtlasMaxPossibleNumberOfTiles() const {
    if(m_mapConfigJSON.contains("width") && m_tileAtlasJSON.contains("tile_size")) {
        if(m_mapConfigJSON.at("width").get<int>() * m_tileAtlasJSON.at("tile_size").get<int>()) {
            return 0;//todo
        }
    }
    return 0;
}

uint32_t LevelConfig::getMapWidth() const {
    return m_mapConfigJSON.at("width").get<uint32_t>(); 
}

std::string LevelConfig::getMapName() const {
    return m_levelConfigJSON.at("name").get<std::string>(); 
}

uint32_t LevelConfig::getTileAtlasTileSize() const {
    return m_tileAtlasJSON.at("tile_size").get<uint32_t>(); 
}

uint32_t LevelConfig::getTileAtlasColumns() const {
    return m_tileAtlasJSON.at("columns").get<uint32_t>();
}

std::string LevelConfig::getTileAtlasPath() const {
    return m_tileAtlasJSON.at("path").get<std::string>(); // get<std::string> is required here otherwise mingw would give error 
}

TileAtlas LevelConfig::getTileAtlasVisualGrid() const {
    return m_tileAtlasJSON["visual_grid"]; //array with tile ids, using [] because those don't throw error if data is empty/null
}

TileAtlas LevelConfig::getTileAtlasLogicalGrid() const{
    return m_tileAtlasJSON["logical_grid"];
}

LevelConfig::~LevelConfig() {
    m_levelConfigStream.close();
}