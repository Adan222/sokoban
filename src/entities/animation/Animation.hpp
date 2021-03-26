#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

/*
 * This struct represent
 * one frame of animation
*/
struct Frame{
    const sf::IntRect pos;
    const float duration; //in seconds
};

class Animation{
    private:
        //conatiner for all frames
        std::vector<Frame> m_frames;

        int m_currentFrameIndex;
        float m_progres;

    public:
        Animation();
        ~Animation();

        void addFrame(const Frame fr);
        bool update(float deltaTime);
        void reset();

        sf::IntRect getCurrFrame() const;
};