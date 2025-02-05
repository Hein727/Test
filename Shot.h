#pragma once
#include "Obj2d.h"

class ShotManager : public OBJ2DManager
{
private:
    ShotManager() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    ShotManager(const ShotManager&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    ShotManager& operator=(const ShotManager&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static ShotManager& getInstance()
    {
        static ShotManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

private:
    static constexpr int OBJ_MAX = 50;
    OBJ2D objWork[OBJ_MAX];
};

void shotNormal(OBJ2D* obj);
void shotMissile(OBJ2D* obj);
