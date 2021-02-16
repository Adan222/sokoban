#include <map/Map.hpp>

Map::Map () {
   
}

bool Map::createMap(const json &levelConfig) {
    if(!m_tileAtlas.loadFromFile(levelConfig["tile_atlas"]["path"].get<std::string>())) {
        return false;
    }
    auto tileVisualGrid = levelConfig["tile_atlas"]["data"];
    const unsigned int tileAtlasRows = levelConfig["tile_atlas"]["rows"].get<int>();
    const unsigned int tileAtlasCols = levelConfig["tile_atlas"]["columns"].get<int>();
    const unsigned int tileSize = levelConfig["tile_atlas"]["tile_width"].get<int>();

    m_tiles.setPrimitiveType(sf::Quads);
    m_tiles.resize(tileAtlasRows * tileAtlasCols * 4);

    for(int i = 1; i <= tileAtlasRows; i++) {
        for(int j = 1; j <= tileAtlasCols; j++) {

            //transform i,j cords to array number(2d array -> 1d array)
            int tileTypeID = tileVisualGrid[i * tileAtlasCols - (tileAtlasCols - j) - 1];

            //to do TILE ID = 0 -- division by zero
            float textureX = (tileTypeID % tileAtlasCols) * tileSize - 32.0f;
            float textureY = (floor((float)tileTypeID / (float)tileAtlasCols)) * tileSize; 
            
            sf::Vertex *single_tile = &m_tiles[4 * (i * tileAtlasCols - (tileAtlasCols - j) - 1)];
            
            single_tile[0].position = sf::Vector2f((j - 1) * tileSize,(i - 1) * tileSize);
            single_tile[1].position = sf::Vector2f((j - 1) * tileSize, (i - 1) * tileSize + tileSize);
            single_tile[2].position = sf::Vector2f((j - 1) * tileSize + tileSize, (i - 1) * tileSize + tileSize);
            single_tile[3].position = sf::Vector2f((j - 1) * tileSize + tileSize, (i - 1) * tileSize);

            single_tile[0].texCoords = sf::Vector2f(textureX, textureY);
            single_tile[1].texCoords = sf::Vector2f(textureX + tileSize - 1, textureY);
            single_tile[2].texCoords = sf::Vector2f(textureX + tileSize - 1, textureY + tileSize - 1);
            single_tile[3].texCoords = sf::Vector2f(textureX, textureY + tileSize - 1);


            std::cout << "textureX: " << textureX << " textureY: " << textureY<< std::endl;
       }
    }




    return true;
}
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileAtlas;

        // draw the vertex array
        target.draw(m_tiles, states);
}

Map::~Map() {

}