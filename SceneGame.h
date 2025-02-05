#pragma once
#include "Scene.h"

class SceneGame : public Scene
{
private:
    SceneGame() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    SceneGame(const SceneGame&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    SceneGame& operator=(const SceneGame&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static SceneGame& getInstance()
    {
        static SceneGame instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;

private:
    int state = 0;  // 状態
    int frame = 0;
};
