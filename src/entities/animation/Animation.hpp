#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

struct Frame{
    const sf::Color color;
    const float duration; //in seconds
};

class Animation{

    std::vector<Frame> m_frames;

    int m_currentFrameIndex;
    float m_progres;

    public:
        Animation();
        ~Animation();

        void addFrame(const Frame &fr);
        void update(float deltaTime);
};