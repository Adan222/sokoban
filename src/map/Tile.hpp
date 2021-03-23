#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable, public sf::Transformable {
    uint32_t m_size;
    bool m_selected;
    int m_textureID;
    int m_physicID;
    
    std::vector<sf::Vertex> m_tile;
    sf::Vector2f m_positionOnMap;
    sf::Vector2u m_textureCords;
public:
    void setPosition(uint32_t col, uint32_t row);
    void setTextureCoords(uint32_t atlasCol, uint32_t atlasRow, int textureID);
    void setTexture(uint32_t atlasCol, uint32_t atlasRow, sf::Texture& tileAtlasTexture);
    void noTexture();

    int getTextureID() const;
    bool isSelected() const;
    void isSelected(bool selected);
    sf::Sprite getSprite(sf::Texture &tileAtlasTexture) const;
    sf::Vector2f getPositionOnMap() const;
    sf::Vector2u getTextureCoords();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Tile(uint32_t tileSize);
    Tile(uint32_t tileSize, bool selected);
    ~Tile();
};