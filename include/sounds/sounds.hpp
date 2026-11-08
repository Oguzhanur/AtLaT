#pragma once
#include <raylib.h>
#include <string>

class soundsEffect{
private:
    Sound soundData;
    bool isActive=1;
public:
    soundsEffect(std::string data, float volume) : soundData(LoadSound(data.c_str())) {
        SetSoundVolume(soundData, volume);
            this->playSilent();
    }
    ~soundsEffect() {
        UnloadSound(soundData);
    };

    void setActive(bool data) {
        isActive =data;
        if(isActive){
            this->playSilent();
        }
    };

    void play(){
        this->playSilent();
        if(isActive){
            PlaySound(soundData);
        }
    }

    void playSilent(){ //! SESLER İLK SEFERDE ÇALIŞMIYOR
        PlaySound(soundData);
    }
};