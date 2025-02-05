#pragma once
#include "Scene.h"

class SceneOver : public Scene
{
private:
    SceneOver() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    SceneOver(const SceneOver&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    SceneOver& operator=(const SceneOver&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static SceneOver& getInstance()
    {
        static SceneOver instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;
    void deinit() override;
};
