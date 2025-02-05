#pragma once
#include "Scene.h"

class SceneInit : public IScene
{
private:
    SceneInit() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    SceneInit(const SceneInit&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    SceneInit& operator=(const SceneInit&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static SceneInit& getInstance()
    {
        static SceneInit instance;
        return instance;
    }
    IScene* execute() override;
};

class SceneDeinit : public IScene
{
private:
    SceneDeinit() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    SceneDeinit(const SceneDeinit&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    SceneDeinit& operator=(const SceneDeinit&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static SceneDeinit& getInstance()
    {
        static SceneDeinit instance;
        return instance;
    }
    IScene* execute() override;
};
