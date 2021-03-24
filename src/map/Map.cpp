#include "Map.hpp"
#include "entities/Box.hpp"
#include "level/LevelConfig.hpp"
#include "logicalGrid/LogicalGrid.hpp"
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
    const uint32_t mapColumns = m_levelConfig.getMapColumns();
    const uint32_t tileSize = m_levelConfig.getTileSize();

    //normalize to get rows and cols
    uint32_t row = floor(position2D.y / static_cast<float>(tileSize));
    uint32_t col = floor(position2D.x / static_cast<float>(tileSize));
    uint32_t index = row * mapColumns - (mapColumns - col) + mapColumns;


    return index;
}

sf::Vector2i Map::indexToPos(u_int32_t index) {
    uint32_t gridWidth = WINDOW_WIDTH / m_levelConfig.getTileSize();
    uint32_t gridHeight = WINDOW_HEIGHT / m_levelConfig.getTileSize();
    for(int y = 0; y < gridHeight; y++)
        for(int x = 0; x < gridWidth; x++)
            if(x + y * gridWidth == index)
                return {x, y};
    return {-1, -1};
}

void Map::findOn(const int index) {
    Grid logicalGrid = m_levelConfig.getTileAtlasLogicalGrid();

    int am = logicalGrid.size();
    if(logicalGrid[index] == LOGIC::BOX || logicalGrid[index] == LOGIC::BOX_AND_WIN)
        m_boxesPos.emplace_back(indexToPos(index));
    else if(logicalGrid[index] == LOGIC::PLAYER)
        m_playerPos = indexToPos(index);
    else if(logicalGrid[index] == LOGIC::WIN_PLACE || logicalGrid[index] == LOGIC::BOX_AND_WIN)
        m_winPlaces.emplace_back(indexToPos(index));
    else if(logicalGrid[index] == LOGIC::WALL)
        m_walls.emplace_back(indexToPos(index));
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
    const uint32_t mapColumns = m_levelConfig.getMapColumns();
    const uint32_t tileAtlasColumns = getTileAtlasColumns();
    const uint32_t tileSize = m_levelConfig.getTileSize();

    m_tiles.clear();
    m_tiles.resize(maxAmountOfTiles, Tile(tileSize));

    const Grid visualGrid = m_levelConfig.getTileAtlasVisualGrid();
    const Grid logicalGrid = m_levelConfig.getTileAtlasLogicalGrid();
    int gridSize = 0;

    if(visualGrid.size() == logicalGrid.size())
        //doesn`t matter which Grid
        gridSize = visualGrid.size();

    for(int i = 0; i < gridSize; i++) {
        
        findOn(i);

        //Set logic
        if(!(logicalGrid[i] > MAX_LOGIC))
            m_tiles[i].setLogic(static_cast<LOGIC>(logicalGrid[i]));

        //Set position of Tile
        int x = indexToPos(i).x;
        int y = indexToPos(i).y;

        m_tiles[i].setPosition(x, y);

        //Set texture of Tile
        int textureID = visualGrid[i];
        if(textureID == -1) //-1 is default no texture
            m_tiles[i].noTexture();
        else {
            float textureX = (textureID % tileAtlasColumns);
            float textureY = (floor((float)textureID / (float)tileAtlasColumns)); 

            m_tiles[i].setTextureCoords(textureX, textureY, textureID);
        }
    }
}

Positions Map::getBoxesPos() const {
    return m_boxesPos;
}

Positions Map::getWallsPos() const {
    return m_walls;
}

sf::Vector2i Map::getPlayerPos() const {
    return m_playerPos;
}

uint32_t Map::getBoxesAmount() const {
    return m_boxesPos.size();
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

