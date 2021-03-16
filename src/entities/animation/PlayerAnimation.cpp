#include "PlayerAnimation.hpp"
#include "entities/Player.hpp"

PlayerAnimation::PlayerAnimation(Player &player) :
    m_player(player),
    m_currentAnimation(WAIT),
    m_lastAniamtion(WAIT)
{
    initAniamtion();
}

PlayerAnimation::~PlayerAnimation() {}

void PlayerAnimation::initAniamtion(){

    int size = m_animations.size()-1;
    for(int i = 0; i < size; i++){
        m_animations[i].addFrame({sf::Color::Red, 1});
        m_animations[i].addFrame({sf::Color::Green, 1});
        m_animations[i].addFrame({sf::Color::Blue, 1});
    }

    m_animations[WAIT].addFrame({sf::Color::White, 1});
}

void PlayerAnimation::update(float deltaTime){

    sf::Color col = m_animations[m_currentAnimation].getColor();

    if(m_animations[m_currentAnimation].update(deltaTime))
        m_player.setTexture(col);
}

void PlayerAnimation::changeAniamtion(AniamtionType an){

    //before change, restart current aniamtion
    /* to think about */
    m_animations[m_currentAnimation].reset();

    //swap current aniamtion to last animation
    m_lastAniamtion = m_currentAnimation;

    //and change
    m_currentAnimation = an;
}

sf::Color PlayerAnimation::starterAniamtion() const{
    return m_animations[m_currentAnimation].getColor();
}