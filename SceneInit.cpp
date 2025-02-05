#include "SceneInit.h"
#include "./GameLib/game_lib.h"
#include "SpriteData.h"
#include "SceneTitle.h"
#include "AudioManager.h"

IScene* SceneInit::execute()
{
    GameLib::init(L"C++ Shooting Game", SCREEN_WIDTH, SCREEN_HEIGHT, false);
    GameLib::texture::load(loadTexture);
    GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
    AudioManager::loadAudio();
    return &SceneTitle::getInstance(); // タイトルへ
}

IScene* SceneDeinit::execute()
{
    AudioManager::unloadAudio();
    GameLib::texture::release(loadTexture);
    GameLib::uninit();
    return nullptr; // ループ終了へ
}
