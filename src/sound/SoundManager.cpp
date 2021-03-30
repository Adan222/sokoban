#include "SoundManager.hpp"


SoundManager::SoundManager() {
    m_soundEngine.init();

    m_sounds.fill(SoLoud::Wav{});
    getSound<Type::Theme>().setVolume(30);
    
}

SoundManager::~SoundManager() {
    m_soundEngine.deinit();
}

