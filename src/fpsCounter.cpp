#include "fpsCounter.hpp"

fpsCounter::fpsCounter(int windowWidth){

    const std::string arialPath = std::string(FONT_DIR) + "arial.ttf";
    //This will display error message
    m_arial.loadFromFile(arialPath);

    m_fpsText.setFont(m_arial);
    m_fpsText.setString("0");

    //origin is set to lefr corner so it will
    //display exacly in right corner
    //now it get width of single char so it have to be double(triple)
    sf::FloatRect textWidth = m_fpsText.getLocalBounds();
    m_fpsText.setPosition(windowWidth - (textWidth.width * 3), 0);

    m_fpsText.setFillColor(sf::Color::White);
}

fpsCounter::~fpsCounter() {}

void fpsCounter::draw(sf::RenderTarget& renderer, sf::RenderStates states) const{
    renderer.draw(m_fpsText);
}

void fpsCounter::update(float deltaTime){

    //set displayed text to counted fps
    m_fpsText.setString(std::to_string(
        static_cast<int>(1.0f / deltaTime
    )));
}