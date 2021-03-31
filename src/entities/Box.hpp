#pragma once

#include "Entity.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>
#include <filesystem>

class Box;
typedef std::vector<Box> Boxes;

class Box : public Entity{
    private:
        sf::Sprite m_boxShape;
        sf::Texture m_boxTexture;
        bool m_imChosen;

    public:
        Box();
        ~Box();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void imChosenOne();
        void imNotChosenOne();
        bool checkIfImChosen() const;
};