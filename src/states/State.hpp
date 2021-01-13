#pragma once

class State {
public:
    State() = default;
    virtual ~State() = default;

    virtual void eventHandler() = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;    
};