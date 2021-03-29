#pragma once

#include <filesystem>
#include <array>
#include <type_traits>

#include <SFML/Audio.hpp>

class SoundManager {
public:
    enum Type {
        Theme,
        Boxes,
        Win,
        PlayerEngine,
        TypeCount
    };

private:
    std::array<sf::SoundBuffer, Type::TypeCount> m_buffers;
    std::array<sf::Sound, Type::TypeCount> m_sounds;
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
    bool setFile(const std::filesystem::path& path) {
        if (T == TypeCount) 
            return false;
        
        if(!getBuffer<T>().loadFromFile(path.generic_string())) 
            return false;

        getSound<T>().setBuffer(getBuffer<T>());
        if constexpr (T == Type::Theme || T == Type::PlayerEngine)
            getSound<T>().setLoop(true);
        
        return true;
    }
    
    template <Type T> 
    sf::Sound& getSound() {
        return m_sounds[T];
    }




    SoundManager();
    ~SoundManager();
};