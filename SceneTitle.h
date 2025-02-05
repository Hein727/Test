#pragma once
#include "Scene.h"

class SceneTitle : public Scene
{
private:
    SceneTitle() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    SceneTitle(const SceneTitle&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    SceneTitle& operator=(const SceneTitle&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static SceneTitle& getInstance()
    {
        static SceneTitle instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;
    void deinit() override;
};
