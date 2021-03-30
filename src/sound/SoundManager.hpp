#pragma once

#include <filesystem>
#include <array>
#include <type_traits>

#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"

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
    SoLoud::Soloud m_soundEngine;
    std::array<SoLoud::Wav, Type::TypeCount> m_sounds;
   
   /* template <Type T> 
    sf::SoundBuffer& getBuffer() {
        return m_buffers[T];
    }
    
    template <Type T> 
    void setSound(sf::Sound m_sound) {
        m_sounds[T] = m_sound;
    }
*/



    

public:
    template <Type T> 
    SoLoud::Wav& getSound() {
        return m_sounds[T];
    }
    template <Type T> 
    bool setFile(const std::filesystem::path& path) {
        if (T == TypeCount) 
            return false;
        
        if(!getSound<T>().load(path.generic_string().c_str())) 
            return false;

        if constexpr (T == Type::Theme || T == Type::PlayerEngine)
            getSound<T>().setLooping(true);
        
        return true;
    }
    


    template <Type T>
    void play() {
        m_soundEngine.play(getSound<T>());

    } 
    
    SoundManager();
    ~SoundManager();
};