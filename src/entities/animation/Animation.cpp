#include "Animation.hpp"

Animation::Animation() :
    m_progres(0),
    m_currentFrameIndex(0)
{
    std::cout << "Animaton constructor\n";
}

Animation::~Animation() {}

void Animation::addFrame(const Frame &fr){
    m_frames.emplace_back(fr);
}

void Animation::update(float deltaTime){
    
    //std::cout << "index: " << m_currentFrameIndex << "\n";

    if(m_progres > m_frames[m_currentFrameIndex].duration){
        m_currentFrameIndex++;

        if(m_currentFrameIndex > m_frames.size()-1)
            m_currentFrameIndex = 0;

        //m_player.setTexture(m_frames[m_currentFrameIndex].color);
        m_progres = 0;

        std::cout << "Color update\n";
    }

    m_progres += deltaTime;
}