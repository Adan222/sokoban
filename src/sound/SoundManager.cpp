#include "SoundManager.hpp"


SoundManager::SoundManager() {
    m_buffers.fill(sf::SoundBuffer{});
    m_sounds.fill(sf::Sound{});
    
}

SoundManager::~SoundManager() {

}

template <SoundManager::Type T> 
bool SoundManager::setFile(const std::filesystem::path& path) {
    if(!getBuffer<T>.loadFromFile(path)) return false;
    getSound<T>.setBuffer(getBuffer<T>);
    if constexpr (std::is_same_v<T, Type::Theme>) {
        getSound<T>.setLoop(true);
    } 
    return true;
}