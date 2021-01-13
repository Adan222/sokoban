#include <vector>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "states/State.hpp"
#include "states/PlayingState.hpp"

class Game {
private:
    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<State::State>> m_states;
    
    State::State& getCurrentState() const;
    void pushState(std::unique_ptr<State::State> state);
    void popState();

    void handleEvent();


public:
    Game();
    ~Game();
    void run();
};