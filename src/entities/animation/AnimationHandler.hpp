#pragma once

#include <array>

#include "Animation.hpp"

//Forward declaration
class Player;
enum DIRECTION : int;

typedef DIRECTION AniamtionType;

class AnimationHandler{
    private:

        Player &m_player;

        AniamtionType m_currentAnimation;

        std::array<Animation, 5> m_animations;

        void initAniamtion();

    public:
        AnimationHandler(Player &player);
        ~AnimationHandler();

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