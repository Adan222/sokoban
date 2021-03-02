#include "Map.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

Map::Map () {
   
}

bool Map::createMap(const json &levelConfig) {
    //try to open texture file
    if(!m_tileAtlas.loadFromFile(levelConfig.at("map").at("tile_atlas").at("path").get<std::string>()))
        throw std::runtime_error("Can`t open file" + levelConfig.at("map").at("tile_atlas").at("path").get<std::string>());
    
    
    using std::cout;


    auto mapConfig = levelConfig.at("map");
    auto tileAtlas = mapConfig.at("tile_atlas");

    auto tileVisualGrid = tileAtlas.at("data"); //array with tile ids
    const unsigned int mapTileWidth = mapConfig.at("width").get<int>(); //amount of tiles per row
    const unsigned int mapTileHeight = ceil((float)tileVisualGrid.size() / (float)mapTileWidth); //calculating amount of rows

    const unsigned int tileAtlasRows = tileAtlas.at("rows").get<int>(); //tile map (.png) rows
    const unsigned int tileAtlasCols = tileAtlas.at("columns").get<int>(); //tile map (.png) cols
    const unsigned int tileSize = tileAtlas.at("tile_size").get<int>(); 

    //tiles are quads
    m_tiles.setPrimitiveType(sf::Quads);

    //resizing by 4 cause m_tiles is vertex vector, so one tile has 4 points
    m_tiles.resize(tileVisualGrid.size() * 4);
   
    unsigned int actualTileElementID = 0;
    unsigned int row = 0;
    unsigned int col = 0;
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