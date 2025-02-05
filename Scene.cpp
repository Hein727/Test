#include "Scene.h"
#include "./GameLib/game_lib.h"
#include "SpriteData.h"
#include "AudioManager.h"
#include "SceneInit.h"

IScene* Scene::execute()
{
    pNextScene = nullptr;
    init();
    // メインループ
    while (GameLib::gameLoop())// Escが押されるとpNextSceneがnullptrのままループを抜ける
    {
        GameLib::input::update();
        GameLib::music::update();

        update();
        draw();

        //GameLib::debug::setString("SAMPLE");
        GameLib::debug::display(1, 1, 1, 2, 2);
        GameLib::present(1, 0);

        if (pNextScene != nullptr) { break; }
    }
    deinit();
    return (pNextScene) ? pNextScene : &SceneDeinit::getInstance();
}

//----------------------------------------------------------------
// SceneManager

void SceneManager::execute(IScene& scene)
{
    IScene* pScene = &scene;
    while (pScene)
    {
        pScene = pScene->execute();
    }
}
