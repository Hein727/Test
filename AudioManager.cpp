#include "AudioManager.h"
#include "./GameLib/game_lib.h"

void AudioManager::loadAudio()
{
    loadMusic();
    setMusicVolume();
    loadSound();
    setSoundVolume();
}

void AudioManager::unloadAudio()
{
    GameLib::music::clear();
}

void AudioManager::loadMusic()
{
    GameLib::music::load(Music::GP1_COURSE_INTRO,   AudioPaths::Music::GP1_COURSE_INTRO);
    GameLib::music::load(Music::IN_GAME,            AudioPaths::Music::IN_GAME);
    GameLib::music::load(Music::BOSS,               AudioPaths::Music::BOSS);
    GameLib::music::load(Music::GAME_CLEAR,         AudioPaths::Music::GAME_CLEAR);
    GameLib::music::load(Music::GAME_OVER,          AudioPaths::Music::GAME_OVER);
    GameLib::music::load(Music::WARNING,            AudioPaths::Music::WARNING);
}

void AudioManager::setMusicVolume()
{
    GameLib::music::setVolume(Music::WARNING, 1.0f);
}

void AudioManager::loadSound()
{
    GameLib::sound::load(Sound::SYSTEM,             AudioPaths::Sound::SYSTEM);
    GameLib::sound::load(Sound::STAGE1,             AudioPaths::Sound::STAGE1);
}

void AudioManager::setSoundVolume()
{
    GameLib::sound::setVolume(Sound::STAGE1, Stage1::SHOT, 1.0f);
}

