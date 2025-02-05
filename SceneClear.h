#pragma once
#include "Scene.h"

class SceneClear : public Scene
{
private:
    SceneClear() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    SceneClear(const SceneClear&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    SceneClear& operator=(const SceneClear&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static SceneClear& getInstance()
    {
        static SceneClear instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;
    void deinit() override;
};
