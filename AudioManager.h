#pragma once

namespace AudioPaths
{
    namespace Music
    {
        inline const wchar_t* GP1_COURSE_INTRO  = L"./Data/Musics/bgm_maoudamashii_8bit29.wav";
        inline const wchar_t* IN_GAME           = L"./Data/Musics/maou_bgm_8bit27.wav";
        inline const wchar_t* BOSS              = L"./Data/Musics/maou_bgm_8bit25.wav";
        inline const wchar_t* GAME_CLEAR        = L"./Data/Musics/maou_bgm_8bit22.wav";
        inline const wchar_t* GAME_OVER         = L"./Data/Musics/maou_bgm_8bit20.wav";
        inline const wchar_t* WARNING           = L"./Data/Musics/meka_ge_keihou06.wav";
    }

    namespace Sound
    {
        inline const wchar_t* SYSTEM = L"./Data/Sounds/system.xwb";
        inline const wchar_t* STAGE1 = L"./Data/Sounds/stage1.xwb";
    }
}

class AudioManager
{
public:
    enum Music
    {
        GP1_COURSE_INTRO,
        IN_GAME, 
        BOSS, 
        GAME_CLEAR, 
        GAME_OVER, 
        WARNING, 
    };

    enum Sound
    {
        SYSTEM, 
        STAGE1, 
    };

    enum System
    {
        KATI,
        START,
    };

    enum Stage1
    {
        COIN, 
        JUMP, 
        SHOT, 
        MISSILE, 
        LASER, 
        BOMB, 
    };

    AudioManager() = default;
    ~AudioManager() = default;

    static void loadAudio();
    static void unloadAudio();

private:
    static void loadMusic();
    static void setMusicVolume();
    static void loadSound();
    static void setSoundVolume();
};
