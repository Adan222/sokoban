#pragma once

#include <filesystem>
#include <array>
#include <type_traits>

#include <SFML/Audio.hpp>

class SoundManager {
    std::array<sf::SoundBuffer, 3> m_buffers;
    std::array<sf::Sound, 3> m_sounds;
    
public:
    enum Type {
        Theme,
        Boxes,
        Win
    };
   
    template <Type T> 
    void setBuffer(sf::SoundBuffer m_buffer) {
        m_buffers[T] = m_buffer;
    }

    template <Type T> 
    sf::SoundBuffer& getBuffer() {
        return m_buffers[T];
    }
    
    template <Type T> 
    void setSound(sf::Sound m_sound) {
        m_sounds[T] = m_sound;
    }




public:
    template <Type T> 
    bool SoundManager::setFile(const std::filesystem::path& path);
    
    template <Type T> 
    sf::Sound& getSound() {
        return m_sounds[T];
    }




    SoundManager();
    ~SoundManager();
};