#include "Map.hpp"



Map::Map () {
   
}

bool Map::createMap(const LevelConfig &levelConfig) {
    using std::cout;
    //try to open texture(tile atlas) file
    if(!m_tileAtlas.loadFromFile(levelConfig.getTileAtlasPath().generic_string()))
        throw std::runtime_error("Can`t open file" + levelConfig.getTileAtlasPath().generic_string());
    

    auto tileVisualGrid = levelConfig.getTileAtlasVisualGrid(); 
    const uint32_t mapTileWidth = levelConfig.getMapWidth();
    const uint32_t tileAtlasCols = levelConfig.getTileAtlasColumns(); 
    const uint32_t tileSize = levelConfig.getTileAtlasTileSize(); 

    //tiles are quads
    m_tiles.setPrimitiveType(sf::Quads);

    //resizing by 4 cause m_tiles is vertex vector, so one tile has 4 points
    m_tiles.resize(tileVisualGrid.size() * 4);
   
    uint32_t actualTileElementID = 0;
    uint32_t row = 0;
    uint32_t col = 0;
    while(actualTileElementID < tileVisualGrid.size()) {
        int tileTypeID = tileVisualGrid[actualTileElementID];

        float textureX = (tileTypeID % tileAtlasCols) * tileSize;
        float textureY = (floor((float)tileTypeID / (float)tileAtlasCols)) * tileSize; 

        sf::Vertex *single_tile = &m_tiles[actualTileElementID * 4];

        //setting position for quads 
        single_tile[0].position = sf::Vector2f(col * tileSize , row * tileSize);
        single_tile[1].position = sf::Vector2f(col * tileSize + tileSize, row * tileSize);
        single_tile[2].position = sf::Vector2f(col * tileSize + tileSize, row * tileSize  + tileSize);
        single_tile[3].position = sf::Vector2f(col * tileSize, row * tileSize + tileSize);
        
        //setting texture cords for quad from tile atlas .png
        single_tile[0].texCoords = sf::Vector2f(textureX, textureY);
        single_tile[1].texCoords = sf::Vector2f(textureX + tileSize, textureY);
        single_tile[2].texCoords = sf::Vector2f(textureX + tileSize, textureY + tileSize);
        single_tile[3].texCoords = sf::Vector2f(textureX, textureY + tileSize);


        cout << "textureX: " << textureX << " textureY + tileSize: " <<  textureY + tileSize << "\n";
        //new row
        if(actualTileElementID % mapTileWidth == (mapTileWidth - 1)) row++;
 
        actualTileElementID++;
        //new column
        col = actualTileElementID % mapTileWidth;
    }

    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &m_tileAtlas;

        target.draw(m_tiles, states);
}

Map::~Map() {

}