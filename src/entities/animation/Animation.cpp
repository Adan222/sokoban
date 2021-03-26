#include "Animation.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

Animation::Animation() :
    m_progres(0),
    m_currentFrameIndex(0)
{
    m_frames.reserve(4);
}

Animation::~Animation() {}

void Animation::addFrame(const Frame fr){
    m_frames.push_back(fr);
}

bool Animation::update(float deltaTime){
    
    if(m_progres > m_frames[m_currentFrameIndex].duration){
        m_currentFrameIndex++;

        if(m_currentFrameIndex > m_frames.size()-1)
            m_currentFrameIndex = 0;

        m_progres = 0;
        return true;
    }

    m_progres += deltaTime;
    return false;
}

void Animation::reset(){
    m_currentFrameIndex = 0;
    m_progres = 0;
}

sf::IntRect Animation::getCurrFrame() const{
    return m_frames[m_currentFrameIndex].pos;
}