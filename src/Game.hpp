#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "states/State.hpp"
#include "states/PlayingState.hpp"

class Game {
private:
    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<State>> m_states;
    void pushState(std::unique_ptr<State> state);
    State& getCurrentState() const;
    void popState();

public:
    Game();
    ~Game();
    void run();
};