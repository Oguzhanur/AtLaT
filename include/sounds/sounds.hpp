#pragma once
#include <raylib.h>
#include <string>

class soundsEffect{
private:
    Sound soundData;
public:
    soundsEffect(std::string data, float volume) : soundData(LoadSound(data.c_str())) {
        SetSoundVolume(soundData, volume);
    }
    ~soundsEffect() {
        UnloadSound(soundData);
    };

    void play(){
        PlaySound(soundData);
    }
};