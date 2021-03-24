#include "FpsCounter.hpp"

FpsCounter::FpsCounter(int windowWidth){

    const std::string arialPath = "../res/font/Minecraft.ttf";
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

FpsCounter::~FpsCounter() {}

void FpsCounter::draw(sf::RenderTarget& renderer, sf::RenderStates states) const{
    renderer.draw(m_fpsText);
}

void FpsCounter::update(float deltaTime){

    //set displayed text to counted fps
    m_fpsText.setString(std::to_string(
        static_cast<int>(1.0f / deltaTime
    )));
}