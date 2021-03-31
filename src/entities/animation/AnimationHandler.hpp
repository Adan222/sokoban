#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <array>

#include "Animation.hpp"

//Forward declaration
class Player;
enum DIRECTION : int;


class AnimationHandler{
    private:

        Player &m_player;

        DIRECTION m_currentAnimation;

        std::array<Animation, 5> m_animations;

        void initAnimation();

    public:
        AnimationHandler(Player &player);
        ~AnimationHandler();

        void update(float deltaTime);
        void changeAnimation(DIRECTION an);
        
        /*
         * This should be call only once
         * in player initalization.
         * This function just return color
         * of current frame 
        */
        sf::IntRect starterAniamtion() const;
};