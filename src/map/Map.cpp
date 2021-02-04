#include <map/Map.hpp>

Map::Map () {
   
}

bool Map::createMap(const json &levelConfig) {
    if(!m_tileAtlas.loadFromFile(levelConfig["tile_atlas"]["path"].get<std::string>())) {
        return false;
    }
    auto tileAtlasRows = levelConfig["tile_atlas"]["rows"].get<int>();
   auto tileAtlasCols = levelConfig["tile_atlas"]["columns"].get<int>();
   auto tileSize = levelConfig["tile_atlas"]["tile_width"].get<int>();

    m_tiles.resize(tileAtlasRows * tileAtlasCols);

    for(int i = 0; i < tileAtlasRows; i++) {
        for(int j = 0; j < tileAtlasCols; j++) {
            
       }
    }




    return true;
}

Map::~Map() {

}