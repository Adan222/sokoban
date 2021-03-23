#include "AnimationHandler.hpp"
#include "entities/Player.hpp"

AnimationHandler::AnimationHandler(Player &player) :
    m_player(player),
    m_currentAnimation(NONE)
{
    initAniamtion();
}

AnimationHandler::~AnimationHandler() {}

void AnimationHandler::initAniamtion(){

    int size = m_animations.size()-1;
    for(int i = 0; i < size; i++){
        m_animations[i].addFrame({sf::Color::Red, 0.2});
        m_animations[i].addFrame({sf::Color::Green, 0.2});
        m_animations[i].addFrame({sf::Color::Blue, 0.2});
    }

    m_animations[NONE].addFrame({sf::Color::White, 0.2});
}

void AnimationHandler::update(float deltaTime){

    sf::Color col = m_animations[m_currentAnimation].getColor();

    if(m_animations[m_currentAnimation].update(deltaTime))
        m_player.setTexture(col);
}

void AnimationHandler::changeAniamtion(AniamtionType an){

    //before change, restart current aniamtion
    /* to think about */
    m_animations[m_currentAnimation].reset();

    //and change
    m_currentAnimation = an;
}

sf::Color AnimationHandler::starterAniamtion() const{
    return m_animations[m_currentAnimation].getColor();
}