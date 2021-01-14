#include "PlayingState.hpp"
namespace State {

    PlayingState::PlayingState() : m_shape(30.0f) {
        m_shape.setFillColor(sf::Color::Green);
        
    }
    bool PlayingState::wantTerminateSelf() {
        return m_popSelf;
    }


    void PlayingState::draw(sf::RenderTarget& renderer) {
        renderer.draw(m_shape);
    }

    void PlayingState::handleEvent(sf::Event e) {
        
    }

    PlayingState::~PlayingState() {

    }

}
