#include "Map.hpp"
#include <exception>

Map::Map(const LevelConfig& levelConfig) :
    m_levelConfig(levelConfig)
{}

Map::~Map() {}

void Map::initMap(){
    loadTexture();
    createMap();
}

void Map::loadTexture(){
    try{
        const std::string path = "../res/graphics/" + m_levelConfig.getTileAtlasPath();

        //try to open texture(tile atlas) file
        if(!m_tileAtlas.loadFromFile(path))
            throw std::runtime_error("Can`t open file: " + path);
        //TO DO check size of tile map, (size + 1) % tilesize
    }
    catch(std::exception &e){
        std::cout << e.what() << "\n";
    }
}

bool Map::createMap() {
    try{
        auto tileVisualGrid = m_levelConfig.getTileAtlasVisualGrid();

        //Check tiles amount
        if(tileVisualGrid.size() > 192 || tileVisualGrid.size() == 0)
            throw std::runtime_error("Bad tiles amount");

        const uint32_t mapTileWidth = m_levelConfig.getMapWidth();
        const uint32_t tileAtlasCols = m_levelConfig.getTileAtlasColumns(); 
        const uint32_t tileSize = m_levelConfig.getTileAtlasTileSize(); 

        //tiles are quads
        m_tiles.setPrimitiveType(sf::Quads);

        //resizing by 4 cause m_tiles is vertex vector, so one tile has 4 points
        m_tiles.resize(tileVisualGrid.size() * 4);
    
        uint32_t col = 0, row = 0, actualTileElementID = 0;
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
            
            //setting texture cords for quad from tile atlas texture
            single_tile[0].texCoords = sf::Vector2f(textureX, textureY);
            single_tile[1].texCoords = sf::Vector2f(textureX + tileSize, textureY);
            single_tile[2].texCoords = sf::Vector2f(textureX + tileSize, textureY + tileSize);
            single_tile[3].texCoords = sf::Vector2f(textureX, textureY + tileSize);


            //new row
            if(actualTileElementID % mapTileWidth == (mapTileWidth - 1)) row++;
    
            actualTileElementID++;
            //new column
            col = actualTileElementID % mapTileWidth;
        }
    }
    catch(std::exception &e){
        std::cout << e.what() << "\n";
    }

    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &m_tileAtlas;

        target.draw(m_tiles, states);
}

sf::Texture& Map::getTileAtlasTexture(){
    return m_tileAtlas;
}

