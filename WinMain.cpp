// インクルード
#include "GameLib/game_lib.h"
#include "SceneInit.h"
#include "AudioManager.h"

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    SceneManager sceneManager;
    sceneManager.execute(SceneInit::getInstance());
    return 0;
}
