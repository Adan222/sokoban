#include "Map.hpp"
#include <exception>

Map::Map(const LevelConfig& levelConfig) : 
    m_levelConfig(levelConfig) 
{}

Map::~Map() {}

uint64_t Map::convertPositionToIndex(sf::Vector2u position2D) {
    const uint32_t mapColumns = m_levelConfig.getMapColumns();
    const uint32_t tileSize = m_levelConfig.getTileSize();

    //normalize to get rows and cols
    uint32_t row = floor(position2D.y / static_cast<float>(tileSize));
    uint32_t col = floor(position2D.x / static_cast<float>(tileSize));
    uint32_t index = row * mapColumns - (mapColumns - col) + mapColumns;

    return index;
}


void Map::updateTile(Tile &selectedTile) {
    uint32_t indexInArray = convertPositionToIndex(selectedTile.getPositionOnMap());
    m_tiles[indexInArray] = selectedTile;
}

void Map::loadTexture() {
    const auto tileAtlasPath = m_levelConfig.getTileAtlasPath();
    try{
        //try to open texture(tile atlas) file
        if(!m_tileAtlas.loadFromFile("../res/graphics/" + tileAtlasPath.generic_string()))
            throw std::runtime_error("Can`t open file: ../res/graphics/" + tileAtlasPath.generic_string());
            //TO DO check size of tile map, (size + 1) % tilesize
    }catch(std::exception &e){
        std::cout << e.what() << "\n";
    }
}



void Map::createMap() {
    const uint32_t maxAmountOfTiles = m_levelConfig.getMapTilesAmount();
    const auto visualGrid = m_levelConfig.getTileAtlasVisualGrid();
    const uint32_t mapColumns = m_levelConfig.getMapColumns();
    const uint32_t tileAtlasColumns = getTileAtlasColumns();
    const uint32_t tileSize = m_levelConfig.getTileSize();

    m_tiles.clear();
    m_tiles.resize(maxAmountOfTiles, Tile(tileSize));


    uint32_t col = 0, row = 0, actualTileElementID = 0;
    while(actualTileElementID < visualGrid.size()) {
        int textureID = visualGrid[actualTileElementID];

        float textureX = (textureID % tileAtlasColumns);
        float textureY = (floor((float)textureID / (float)tileAtlasColumns)); 

        m_tiles[actualTileElementID].setPosition(col, row);
        
        
        if(textureID == -1) { //-1 is default no texture
            m_tiles[actualTileElementID].noTexture();
        } else {
            m_tiles[actualTileElementID].setTextureCoords(textureX, textureY, textureID);
        }


        
        if(actualTileElementID % mapColumns == (mapColumns - 1)) 
            ++row; //new row
        
        ++actualTileElementID;
        col = actualTileElementID % mapColumns; //new column
    }
}

void Map::createGrid() {
    const uint32_t maxAmountOfTiles = m_levelConfig.getMapTilesAmount();
    const uint32_t mapColumns = m_levelConfig.getMapColumns();
    const uint32_t tileSize = m_levelConfig.getTileSize();

    m_gridSquares.clear();
    m_gridSquares.resize(maxAmountOfTiles);

    uint32_t row = 0, column = 0;
    for(int i = 0; auto& square : m_gridSquares) {
        ++i;
        square.setSize(sf::Vector2f(tileSize, tileSize));
        square.setOutlineColor(sf::Color(255, 255, 255, 150));
        square.setFillColor(sf::Color::Transparent);
        square.setOutlineThickness(0.5);
        if(column == mapColumns) {
            column = 0;
            ++row;
        }
        square.setPosition(column * tileSize, row * tileSize);        
        ++column;
    }
}

sf::Texture& Map::getTileAtlasTexture() {
    return m_tileAtlas;
}

uint32_t Map::getTileAtlasColumns() {
    return (getTileAtlasTexture().getSize().x + 1) / m_levelConfig.getTileSize();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileAtlas;

    for(const auto& tile : m_tiles) {
        target.draw(tile, states);
    }
    for(const auto& square : m_gridSquares) {
        target.draw(square);
    }
    
}

