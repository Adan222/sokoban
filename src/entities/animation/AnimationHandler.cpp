#include "AnimationHandler.hpp"
#include "entities/Entity.hpp"
#include "entities/Player.hpp"
#include <SFML/Graphics/Rect.hpp>

AnimationHandler::AnimationHandler(Player &player) :
    m_player(player),
    m_currentAnimation(LEFT)
{
    initAniamtion();
}

AnimationHandler::~AnimationHandler() {}

void AnimationHandler::initAniamtion(){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            sf::IntRect pos = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            m_animations[i].addFrame({pos, 0.1});
        }
    }
}   

void AnimationHandler::update(float deltaTime){

    sf::IntRect pos = m_animations[m_currentAnimation].getCurrFrame();

    if(m_animations[m_currentAnimation].update(deltaTime))
        m_player.setTexture(pos);
}

void AnimationHandler::changeAniamtion(AniamtionType an){

    //before change, restart current aniamtion
    /* to think about */
    m_animations[m_currentAnimation].reset();

    //and change
    m_currentAnimation = an;
}

sf::IntRect AnimationHandler::starterAniamtion() const{
    return m_animations[m_currentAnimation].getCurrFrame();
}