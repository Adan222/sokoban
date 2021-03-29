#include "SoundManager.hpp"


SoundManager::SoundManager() {
    m_buffers.fill(sf::SoundBuffer{});
    m_sounds.fill(sf::Sound{});

    getSound<Type::Theme>().setVolume(30);
    
}

SoundManager::~SoundManager() {

}

