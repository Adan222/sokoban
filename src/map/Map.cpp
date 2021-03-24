#include "Map.hpp"
#include "entities/Box.hpp"
#include "level/LevelConfig.hpp"
#include "map/Grid.hpp"
#include <bits/stdint-uintn.h>
#include <exception>

Map::Map(const LevelConfig& levelConfig) : 
    m_levelConfig(levelConfig) 
{
    loadTexture();
    createGrid();
    createMap();
}

Map::~Map() {}

uint32_t Map::convertPositionToIndex(sf::Vector2f position2D) {
    uint32_t index = 0;
   
    if((position2D.y-WINDOW_HEIGHT)* position2D.y <= 0 && (position2D.x-WINDOW_WIDTH) * position2D.x <= 0) { //check if number is in range
        const uint32_t mapColumns = m_levelConfig.getMapColumns();
        const uint32_t tileSize = m_levelConfig.getTileSize();

        //normalize to get rows and cols
        uint32_t row = floor(position2D.y / static_cast<float>(tileSize));
        uint32_t col = floor(position2D.x / static_cast<float>(tileSize));
        index = row * mapColumns - (mapColumns - col) + mapColumns;
    }

    return index;
}

sf::Vector2i Map::indexToPos(uint32_t index) {
    uint32_t gridWidth = WINDOW_WIDTH / m_levelConfig.getTileSize();
    uint32_t gridHeight = WINDOW_HEIGHT / m_levelConfig.getTileSize();

    for(int y = 0; y < gridHeight; y++)
        for(int x = 0; x < gridWidth; x++)
            if(x + y * gridWidth == index)
                return {x, y};
    return {-1, -1};
}

Positions Map::find(LOGIC what, LOGIC sec) {
    Grid logicalGrid = m_levelConfig.getTileAtlasLogicalGrid();
    Positions pos;

    int am = logicalGrid.size();
    //idk why iterator don`t work here
    for(int i = 0; i < am; i++)
        if(logicalGrid[i] == what || logicalGrid[i] == sec)
            pos.emplace_back(indexToPos(i));

    return pos;
}


void Map::updateTile(Tile &selectedTile) {
    uint32_t indexInArray = convertPositionToIndex(selectedTile.getPositionOnMap());
    m_tiles[indexInArray] = selectedTile;
}

Tile* Map::selectTile(sf::Vector2f mousePosition) {
    uint32_t indexInArray = convertPositionToIndex(mousePosition);
    m_gridSquares[indexInArray].setFillColor(sf::Color(0, 255, 0, 120));
   

    return &m_tiles[indexInArray];
}

void Map::unselectTile(Tile* selectedTile) {
    if(selectedTile != nullptr) {
        uint32_t indexInArray = convertPositionToIndex(selectedTile->getPositionOnMap());
        m_gridSquares[indexInArray].setFillColor(sf::Color::Transparent);
        selectedTile = nullptr;
    }

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
    const uint32_t mapColumns = m_levelConfig.getMapColumns();
    const uint32_t tileAtlasColumns = getTileAtlasColumns();
    const uint32_t tileSize = m_levelConfig.getTileSize();

    m_tiles.clear();
    m_tiles.resize(maxAmountOfTiles, Tile(tileSize));

    const Grid visualGrid = m_levelConfig.getTileAtlasVisualGrid();
    const Grid logicGrid = m_levelConfig.getTileAtlasLogicalGrid();

    for(int i = 0; i < maxAmountOfTiles; i++) {
        
        //Set logic
        if(i < logicGrid.size()){
            m_tiles[i].setLogicID(logicGrid[i]);
        }
        else
            m_tiles[i].setLogicID(0);

        //Set position of Tile
        int x = indexToPos(i).x;
        int y = indexToPos(i).y;

        m_tiles[i].setPosition(x, y);

        //Set texture of Tile
        int textureID = visualGrid[i];

        if(i < visualGrid.size() && textureID != -1){
            float textureX = (textureID % tileAtlasColumns);
            float textureY = (floor((float)textureID / (float)tileAtlasColumns)); 

            m_tiles[i].setTextureCoords(textureX, textureY, textureID);
        }
        else
            m_tiles[i].noTexture();
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

