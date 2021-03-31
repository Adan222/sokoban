#include "SoundManager.hpp"


SoundManager::SoundManager() {
    m_soundEngine.init();
    m_sounds.fill(SoLoud::Wav{});

    getSound<Type::Theme>().setVolume(1);
    getSound<Type::PlayerEngine>().setLooping(true);
    getSound<Type::Theme>().setLooping(true);
}



SoundManager::~SoundManager() {
    m_soundEngine.deinit();
}

