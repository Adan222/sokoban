#include "Map.hpp"
#include "entities/Box.hpp"
#include "level/LevelConfig.hpp"
#include "map/Grid.hpp"
#include <exception>

Map::Map(LevelConfig& levelConfig) : 
    m_levelConfig(levelConfig) 
{}

Map::~Map() {}

uint32_t Map::positionToIndex(sf::Vector2f position2D) {
    uint32_t index = 0;
   
    if((position2D.y-WINDOW_HEIGHT)* position2D.y <= 0 && (position2D.x-WINDOW_WIDTH) * position2D.x <= 0) { //check if number is in range
        const uint32_t mapColumns = m_levelConfig.get().getMapColumns();
        const uint32_t tileSize =  m_levelConfig.get().getTileSize();

        //normalize to get rows and cols
        uint32_t row = floor(position2D.y / static_cast<float>(tileSize));
        uint32_t col = floor(position2D.x / static_cast<float>(tileSize));
        index = row * mapColumns + col;
    }

    return index;
}

sf::Vector2i Map::indexToPosition(uint32_t index) {
    uint32_t gridWidth = WINDOW_WIDTH / m_levelConfig.get().getTileSize();
    uint32_t gridHeight = WINDOW_HEIGHT / m_levelConfig.get().getTileSize();

    for(int y = 0; y < gridHeight; y++)
        for(int x = 0; x < gridWidth; x++)
            if(x + y * gridWidth == index)
                return {x, y};
    return {-1, -1};
}

Positions Map::find(LOGIC what, LOGIC sec) {
    auto logicGrid = m_levelConfig.get().getLogicGrid();
    Positions pos;

    //idk why iterator don`t work here
    for(int i = 0; i < logicGrid.size(); i++)
        if(logicGrid[i] == what || logicGrid[i] == sec)
            pos.emplace_back(indexToPosition(i));

    return pos;
}


void Map::updateTile(Tile &selectedTile) {
    uint32_t indexInArray = positionToIndex(selectedTile.getPositionOnMap());
    m_tiles[indexInArray] = selectedTile;
}

Tile* Map::selectTile(sf::Vector2f mousePosition) {
    uint32_t indexInArray = positionToIndex(mousePosition);
    m_gridSquares[indexInArray].setFillColor(sf::Color(51, 217, 178, 120));
   

    return &m_tiles[indexInArray];
}

void Map::unselectTile(Tile* selectedTile) {
    if(selectedTile != nullptr) {
        uint32_t indexInArray = positionToIndex(selectedTile->getPositionOnMap());
        m_gridSquares[indexInArray].setFillColor(sf::Color::Transparent);
        selectedTile = nullptr;
    }

}

void Map::setLogicGrid(const std::vector<int>& logicGrid) {
    const uint32_t maxAmountOfTiles = m_levelConfig.get().getMapTilesAmount();

    for(int i = 0; i < maxAmountOfTiles; i++) {
        if(i < logicGrid.size())
            m_tiles[i].setLogicID(logicGrid[i]);
        else
            m_tiles[i].setLogicID(0);
    }

}

void Map::saveGrids() {
    std::vector<int> logicGrid;
    std::vector<int> visualGrid;

    for(const auto& t : m_tiles) {
        logicGrid.push_back(t.getLogicID());
        visualGrid.push_back(t.getTextureID());
    }
    m_levelConfig.get().saveLogicGrid(logicGrid);
    m_levelConfig.get().saveVisualGrid(visualGrid);

}

void Map::loadTexture() {
    const auto& tileAtlasPath = m_levelConfig.get().getTileAtlasPath();
    try{
        std::filesystem::path pre = "";
        if(!tileAtlasPath.is_absolute()) pre = "../";
        //try to open texture(tile atlas) file
        if(!m_tileAtlas.loadFromFile(pre.generic_string() + tileAtlasPath.generic_string()))
            throw std::runtime_error("Map: Can`t open file: " + pre.generic_string() + tileAtlasPath.generic_string());
            //TO DO check size of tile map, (size + 1) % tilesize
    }catch(std::exception &e){
        std::cout << "Map: loadTexture: " << e.what() << "\n";
    }
}

void Map::createMap() {
    const uint32_t maxAmountOfTiles = m_levelConfig.get().getMapTilesAmount();
    const uint32_t mapColumns = m_levelConfig.get().getMapColumns();
    const uint32_t tileAtlasColumns = getTileAtlasColumns();
    const uint32_t tileSize = m_levelConfig.get().getTileSize();

    m_tiles.clear();
    m_tiles.resize(maxAmountOfTiles, Tile(tileSize));

    const auto visualGrid = m_levelConfig.get().getVisualGrid();
    const auto logicGrid = m_levelConfig.get().getLogicGrid();

    for(int i = 0; i < maxAmountOfTiles; i++) {
        
        //Set logic
        if(i < logicGrid.size())
            m_tiles[i].setLogicID(logicGrid[i]);
        else
            m_tiles[i].setLogicID(0);

        //Set position of Tile
        int x = indexToPosition(i).x;
        int y = indexToPosition(i).y;

        m_tiles[i].setPosition(x, y);

        //Set texture of Tile
        if(i < visualGrid.size()) {
            int textureID = visualGrid[i];
            if(textureID != -1) {
                float textureX = (textureID % tileAtlasColumns);
                float textureY = (floor((float)textureID / (float)tileAtlasColumns)); 
                m_tiles[i].setTextureCoords(textureX, textureY, textureID);
            } else {
                m_tiles[i].noTexture();
            }
        } else {
            m_tiles[i].noTexture();
        }

    }
}

void Map::createGrid() {
    const uint32_t maxAmountOfTiles = m_levelConfig.get().getMapTilesAmount();
    const uint32_t mapColumns = m_levelConfig.get().getMapColumns();
    const uint32_t tileSize = m_levelConfig.get().getTileSize();


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

const sf::Texture& Map::getTileAtlasTexture() {
    return m_tileAtlas;
}

uint32_t Map::getTileAtlasColumns() {
    return (getTileAtlasTexture().getSize().x + 1) / m_levelConfig.get().getTileSize();
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

