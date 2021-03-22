#include "LevelConfig.hpp"

LevelConfig::LevelConfig(const std::filesystem::path& fileConfigPath)  {
    using json = nlohmann::json;
    using std::cout;
    try {
        m_levelConfigStream.open(fileConfigPath, std::ifstream::in);
        if(!m_levelConfigStream.good()) 
            throw std::runtime_error(fileConfigPath.generic_string() + ": " + std::strerror(errno));

        m_levelConfigJSON = json::parse(m_levelConfigStream); //can throw parsing error, thats why we are using try catch
    } catch(std::exception &e){
        cout << e.what() << "\n";
    }

    //TO DO: maybe wrap in function, do error checking?
    m_mapConfigJSON = m_levelConfigJSON.at("map").get_ref<json::object_t&>();
    m_tileAtlasJSON = m_mapConfigJSON.at("tile_atlas").get_ref<json::object_t&>();
}

LevelConfig::LevelConfig() {
    using json = nlohmann::json;
    m_levelConfigJSON = R"(
    {
        "map" : {
            "name" : "Default",
            "tile_atlas" : {
                "path" : "iso-64x64-outside.png",
                "tile_size": 64
            },
            "visual_grid" : [1, 2, 3, 3],
            "zoom" : 1.0
        }
    }
    )"_json;
    
    m_mapConfigJSON = m_levelConfigJSON.at("map").get_ref<json::object_t&>();
    m_tileAtlasJSON = m_mapConfigJSON.at("tile_atlas").get_ref<json::object_t&>();
    
    
}

uint32_t LevelConfig::getMapTilesAmount() const {
    //we assume that screen res is 1024 x 768
    uint32_t cols = 1024 / getTileSize();
    uint32_t rows = 768 / getTileSize();
    if(getMapColumns() != cols) {
         //throw std::runtime_error("Map width provided in config is not valid for that tile size.");
    }
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



std::filesystem::path LevelConfig::getTileAtlasPath() const{
    return m_tileAtlasJSON.at("path").get<std::string>();
}

void LevelConfig::setTileSize(uint32_t tileSize) {
    m_tileAtlasJSON.at("tile_size") = tileSize;
}

std::vector<int> LevelConfig::getTileAtlasVisualGrid() const {
    return m_mapConfigJSON["visual_grid"];
}



LevelConfig::~LevelConfig() {
    
}