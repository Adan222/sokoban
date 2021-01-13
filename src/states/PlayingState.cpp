#include "PlayingState.hpp"

PlayingState::PlayingState() : m_shape(30.0f) {
    m_shape.setFillColor(sf::Color::Green);
}

void PlayingState::draw(sf::RenderTarget& renderer) {
    renderer.draw(m_shape);
}

void PlayingState::eventHandler() {

}

PlayingState::~PlayingState() {

}