#include "Map.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

Map::Map () {
   
}

bool Map::createMap(const json &levelConfig) {
    using std::cout;
    //try to open texture file
    if(!m_tileAtlas.loadFromFile(levelConfig.at("map").at("tile_atlas").at("path").get<std::string>()))
        throw std::runtime_error("Can`t open file" + levelConfig.at("map").at("tile_atlas").at("path").get<std::string>());
    

    auto mapConfig = levelConfig.at("map");
    auto tileAtlas = mapConfig.at("tile_atlas");

    auto tileVisualGrid = tileAtlas["data"]; //array with tile ids, using [] because those don't throw error if data is empty/null
    
    //better to use uint32_t cus of https://stackoverflow.com/questions/14911813/what-is-the-difference-between-an-uint32-and-an-unsigned-int-in-c
    const uint32_t mapTileWidth = mapConfig.at("width").get<int>(); //amount of tiles per row
    const uint32_t mapTileHeight = ceil((float)tileVisualGrid.size() / (float)mapTileWidth); //calculating amount of rows

    const uint32_t tileAtlasRows = tileAtlas.at("rows").get<int>(); //tile map (.png) rows
    const uint32_t tileAtlasCols = tileAtlas.at("columns").get<int>(); //tile map (.png) cols
    const uint32_t tileSize = tileAtlas.at("tile_size").get<int>(); 

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