#pragma once

#include <array>

#include "Animation.hpp"

class Player;

enum AniamtionType{
    MOVE_UP,
    MOVE_RIGHT,
    MOVE_DOWN,
    MOVE_LEFT,
    WAIT
};

class PlayerAnimation{
    private:

        Player &m_player;

        AniamtionType m_currentAnimation;

        /*
        * Last aniamtion will be used to
        * determine directon which will be set
        * when player will stand in place
        */
        AniamtionType m_lastAniamtion;

        std::array<Animation, 5> m_animations;

        void initAniamtion();

    public:
        PlayerAnimation(Player &player);
        ~PlayerAnimation();

        void update(float deltaTime);
        void changeAniamtion(AniamtionType an);
        
        /*
         * This should be call only once
         * in player initalization.
         * This function just return color
         * of current frame 
        */
        sf::Color starterAniamtion() const;
};