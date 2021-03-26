#include "FpsCounter.hpp"

FpsCounter::FpsCounter(int windowWidth) :
    wText()
{
    setPosition(windowWidth - (getWidth() * 3), 0);
}

FpsCounter::~FpsCounter() {}

void FpsCounter::update(const float deltaTime){

    //set displayed text to counted fps
    setString(std::to_string(
        static_cast<int>(1.0f / deltaTime
    )));
}