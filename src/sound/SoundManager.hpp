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
        TypeCount //get number of elements, not vaild type!
    };

private:
    SoLoud::Soloud m_soundEngine;
    std::array<SoLoud::Wav, Type::TypeCount> m_sounds;


    template <Type T> 
    SoLoud::Wav& getSound() {
        return m_sounds[T];
    }
public:

    template <Type T>
    void play() {
        m_soundEngine.play(getSound<T>());
    } 
    template <Type T>
    void stop() {
        getSound<T>().stop();
    } 
    template <Type T> 
    bool setFile(const std::filesystem::path& path) {
        if constexpr (T == TypeCount) 
            return false;
        
        if(!getSound<T>().load(path.generic_string().c_str())) 
            return false;

        
        
        return true;
    }

    void clear() {
        m_sounds.fill(SoLoud::Wav{});
    }

    
    SoundManager();
    ~SoundManager();
};