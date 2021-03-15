#include "LevelConfig.hpp"

LevelConfig::LevelConfig(const std::filesystem::path& fileConfigPath) {
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

    //to do, maybe wrap in function, do error checking?
    mapConfigJSON = m_levelConfigJSON.at("map");
    tileAtlasJSON = mapConfigJSON.at("tile_atlas");
}


uint32_t LevelConfig::getMapWidth() const {
    return mapConfigJSON.at("width").get<uint32_t>(); 
}

std::string LevelConfig::getMapName() const {
    return mapConfigJSON.at("name").get<std::string>(); 
}


uint32_t LevelConfig::getTileAtlasTileSize() const {
    return tileAtlasJSON.at("tile_size").get<uint32_t>(); 
}

uint32_t LevelConfig::getTileAtlasColumns() const {
    return tileAtlasJSON.at("columns").get<uint32_t>();
}

std::filesystem::path LevelConfig::getTileAtlasPath() const {
    return tileAtlasJSON.at("path"); 
}

std::vector<uint16_t> LevelConfig::getTileAtlasVisualGrid() const {
    return tileAtlasJSON["visual_grid"]; //array with tile ids, using [] because those don't throw error if data is empty/null
}



LevelConfig::~LevelConfig() {
    
}