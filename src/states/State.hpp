#pragma once

#include <SFML/Graphics.hpp>

namespace State {

    class State {
    protected:

        bool m_popSelf;
    public:
    
        State() : m_popSelf(false) {};
        virtual ~State() = default;

        virtual bool wantTerminateSelf() = 0;
        virtual void handleEvent(sf::Event e) = 0;
        virtual void draw(sf::RenderTarget& renderer) = 0;    
    };

}