//#define DEVELOP

#include "SceneDemo.h"
#include <fstream>
#include <iomanip>
#include "./GameLib/game_lib.h"
#include "Stage.h"
#include "SceneTitle.h"
#include "Player.h"

bool saveDemoData();

#ifdef DEVELOP
int demoData[60 * 60];
#else
int demoData[] = {
#include "demo_data.txt"
    -1, 
};
#endif

void SceneDemo::init()
{
    srand(0);   // デモのときは乱数系列をリセット
    timer = 0;
    Stage::getInstance().init();
}

void SceneDemo::update()
{
    using namespace GameLib::input;
#ifdef DEVELOP
    // 終了チェック
    if (TRG(0) & PAD_SELECT || timer == 60 * 60)
    {
        saveDemoData();
        setScene(SceneTitle::getInstance());
        return;
    }
    // データ追加
    demoData[timer] = STATE(0);

    // キー入力を設定しておく
    OBJ2D* player = PlayerManager::getInstance().begin();
    player->iWork[PlayerManager::PAD_STATE] = STATE(0);
    player->iWork[PlayerManager::PAD_TRG] = timer ? TRG(0) : 0;
#else
    // 終了チェック
    if (demoData[timer] == -1 || TRG(0))
    {
        setScene(SceneTitle::getInstance());
        return;
    }
    // デモ再生
    OBJ2D* player = PlayerManager::getInstance().begin();
    player->iWork[PlayerManager::PAD_STATE] = demoData[timer];
    player->iWork[PlayerManager::PAD_TRG] = timer ? demoData[timer] & ~demoData[timer - 1] : 0;
#endif
    Stage::getInstance().update();
    timer++;
}

void SceneDemo::draw()
{
    GameLib::clear(0, 0, 0);
    Stage::getInstance().draw();
#ifdef DEVELOP
    if (timer & 0x20)
    {
        GameLib::font::textOut(4, "Recording gameplay for demo.", { 640, 300 }, { 2, 2 },
            { 0, 1, 1, 1 }, GameLib::TEXT_ALIGN::MIDDLE);
    }
    GameLib::font::textOut(4, "Press Backspace to save.", { 0, 700 });
#else
    if (timer & 0x20)
    {
        GameLib::font::textOut(4, "DEMO", { 640, 300 }, { 2, 2 },
            { 0, 1, 1, 1 }, GameLib::TEXT_ALIGN::MIDDLE);
    }
#endif
}

//----------------------------------------------------------------
// デモデータの保存
bool saveDemoData()
{
    std::ofstream ofs;
    ofs.open("demo_data.txt");
    if (!ofs) return false;

    for (int i = 0; i < 60 * 60; i++)
    {
        ofs << "0x" << std::setfill('0') << std::setw(8) << std::hex << demoData[i] << ", ";
        if (i % 8 == 7)
        {
            ofs << std::endl;
        }
    }

    ofs.close();

    return true;
}
