#include "SceneOver.h"
#include "./GameLib/game_lib.h"
#include "Stage.h"
#include "SceneTitle.h"
#include "AudioManager.h"

void SceneOver::init()
{
    timer = 0;

    GameLib::music::play(AudioManager::Music::GAME_OVER, true);
}

void SceneOver::update()
{
    if (timer > 60 * 15)
    {
        setScene(SceneTitle::getInstance());
    }
    if (timer > 0x40 && GameLib::input::TRG(0))
    {
        setScene(SceneTitle::getInstance());
    }

    timer++;
}

void SceneOver::draw()
{
    GameLib::clear(0, 0, 0);

    Stage::getInstance().draw();

    if (timer & 0x20)
    {
        GameLib::font::textOut(4, "GAME OVER",
            { 640, 360 }, { 5, 5 }, { 1, 0, 0, 1 },
            GameLib::TEXT_ALIGN::MIDDLE);
    }
}

void SceneOver::deinit()
{
    GameLib::music::stop(AudioManager::Music::GAME_OVER);
}
