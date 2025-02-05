#pragma once
#include "Obj2d.h"

class EffectManager : public OBJ2DManager
{
private:
    EffectManager() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    EffectManager(const EffectManager&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    EffectManager& operator=(const EffectManager&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static EffectManager& getInstance()
    {
        static EffectManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

private:
    static constexpr int OBJ_MAX = 100;
    OBJ2D objWork[OBJ_MAX];
};

// プロトタイプ宣言
void effectBomb(OBJ2D* obj);
void effectBomb2(OBJ2D* obj);
