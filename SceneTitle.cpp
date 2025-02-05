#include "SceneTitle.h"
#include "./GameLib/game_lib.h"
#include "SceneGame.h"
#include "SceneDemo.h"
#include "AudioManager.h"

void SceneTitle::init()
{
    timer = 0;

    GameLib::music::play(AudioManager::Music::GP1_COURSE_INTRO, true);
}

void SceneTitle::update()
{
    using namespace GameLib::input;
    if (TRG(0) & PAD_START)
    {
        GameLib::sound::play(AudioManager::Sound::SYSTEM, AudioManager::System::START);

        setScene(SceneGame::getInstance());
        return;
    }

    // 5•bŒã‚Éƒfƒ‚‚ÖØ‚èŠ·‚¦
    if (timer > 60 * 5)
    {
        setScene(SceneDemo::getInstance());
        return;
    }

    timer++;
}

void SceneTitle::draw()
{
    GameLib::clear(0, 0, 0);

    GameLib::font::textOut(4, "C++ Shooting", { 640, 300 }, { 5, 5 },
        { 1, 1, 1, 1 }, GameLib::TEXT_ALIGN::MIDDLE);

    if (timer & 0x20)
    {
        GameLib::font::textOut(4, "Push space key", { 640, 500 }, { 2, 2 },
            { 1, 1, 0, 1 }, GameLib::TEXT_ALIGN::MIDDLE);
    }

    //GameLib::font::textOut(4, "Please wait for the demo.", { 20, 660 }, { 1, 1 }, { 0, 1, 1, 1 });
    //GameLib::font::textOut(4, "Creation and playback are in the demo.", { 20, 680 }, { 1, 1 }, { 0, 1, 1, 1 });
}

void SceneTitle::deinit()
{
    GameLib::music::stop(AudioManager::Music::GP1_COURSE_INTRO);
}
