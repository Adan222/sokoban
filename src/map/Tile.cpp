#include "Tile.hpp"

Tile::Tile(uint32_t tileSize) : m_size(tileSize) {
    m_tile.resize(4);
}
Tile::Tile(uint32_t tileSize, bool selected) : m_size(tileSize), m_selected(selected) {
    m_tile.resize(4);
}


Tile::~Tile() {
    
}

sf::Vector2u Tile::getTextureCoords() {
    return m_textureCords;
}

int Tile::getTextureID() const {
    return m_textureID;
}

bool Tile::isSelected() const {
    return m_selected;
}

void Tile::isSelected(bool selected) {
    m_selected = selected;
}


void Tile::setPosition(uint32_t col, uint32_t row) {
    row *= m_size;
    col *= m_size;
    m_positionOnMap = sf::Vector2f(col, row);
    
    m_tile[0].position = sf::Vector2f(col, row);
    m_tile[1].position = sf::Vector2f(col + m_size, row );
    m_tile[2].position = sf::Vector2f(col + m_size, row + m_size);
    m_tile[3].position = sf::Vector2f(col, row + m_size);
}


void Tile::setTextureCoords(uint32_t atlasCol, uint32_t atlasRow, int textureID) {
    atlasRow *= m_size;
    atlasCol *= m_size;
    m_textureID = textureID;


    m_textureCords = sf::Vector2u(atlasCol, atlasRow);
    m_tile[0].texCoords = sf::Vector2f(atlasCol, atlasRow);
    m_tile[1].texCoords = sf::Vector2f(atlasCol + m_size, atlasRow);
    m_tile[2].texCoords = sf::Vector2f(atlasCol + m_size, atlasRow + m_size);
    m_tile[3].texCoords = sf::Vector2f(atlasCol, atlasRow + m_size);
}

void Tile::setLogic(LOGIC log) {
    m_logic = log;
}



void Tile::noTexture() {
    m_textureID = -1;
    m_tile[0].color = m_tile[1].color = m_tile[2].color = m_tile[3].color = sf::Color::Black;
}


sf::Sprite Tile::getSprite(sf::Texture &tileAtlasTexture) const {
    auto temporarySprite = sf::Sprite(tileAtlasTexture);
    temporarySprite.setTextureRect(sf::IntRect(static_cast<sf::Vector2i>(m_textureCords), sf::Vector2i(m_size, m_size)));
    temporarySprite.setScale(this->getScale());
    return temporarySprite;
}

sf::Vector2f Tile::getPositionOnMap() const {
    return m_positionOnMap;
}


void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!m_tile.empty()) {
        target.draw(&m_tile[0], m_tile.size(), sf::Quads, states);
    }
}
