#include "LevelConfig.hpp"

LevelConfig::LevelConfig(const std::filesystem::path& fileConfigPath)  {
    using json = nlohmann::json;
    using std::cout;
    try {
        m_levelConfigStream.open(fileConfigPath, std::ifstream::in);
        if(!m_levelConfigStream.good()) //TODO: not throwing error if file was not found
            throw std::runtime_error(fileConfigPath.generic_string() + ": " + std::strerror(errno));

        m_levelConfigJSON = json::parse(m_levelConfigStream); //can throw parsing error, thats why we are using try catch
    } catch(std::exception &e){
        cout << e.what() << "\n";
    }

    //TO DO: maybe wrap in function, do error checking?
    m_mapConfigJSON = m_levelConfigJSON.at("map");
    m_tileAtlasJSON = m_mapConfigJSON.at("tile_atlas");
}

uint32_t LevelConfig::getMapMaxTilesAmount() const {
    //we assume that screen res is 1024 to 768
    uint32_t cols = 1024 / getTileAtlasTileSize();
    uint32_t rows = 768 / getTileAtlasTileSize();
    if(getMapWidth() != cols) {
         throw std::runtime_error("Map width provided in config is not valid for that tile size.");
    }
    return cols * rows;
}

uint32_t LevelConfig::getTileAtlasMaxPossibleNumberOfTiles() const {
    if(m_mapConfigJSON.contains("width") && m_tileAtlasJSON.contains("tile_size")) {
        if(m_mapConfigJSON.at("width").get<int>() * m_tileAtlasJSON.at("tile_size").get<int>()) {
            return 0;//todo
        }
    }
}

uint32_t LevelConfig::getMapWidth() const {
    return m_mapConfigJSON.at("width").get<uint32_t>(); 
}

std::string LevelConfig::getMapName() const {
    return m_mapConfigJSON.at("name").get<std::string>(); 
}

uint32_t LevelConfig::getTileAtlasTileSize() const {
    return m_tileAtlasJSON.at("tile_size").get<uint32_t>(); 
}

uint32_t LevelConfig::getTileAtlasColumns() const {
    return m_tileAtlasJSON.at("columns").get<uint32_t>();
}

std::filesystem::path LevelConfig::getTileAtlasPath() const {
    return m_tileAtlasJSON.at("path").get<std::string>(); // get<std::string> is required here otherwise mingw would give error 
}

std::vector<uint16_t> LevelConfig::getTileAtlasVisualGrid() const {
    return m_tileAtlasJSON["visual_grid"]; //array with tile ids, using [] because those don't throw error if data is empty/null
}



LevelConfig::~LevelConfig() {
    
}