#pragma once
#include "Obj2d.h"

class BackManager : public OBJ2DManager
{
private:
    BackManager() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    BackManager(const BackManager&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    BackManager& operator=(const BackManager&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static BackManager& getInstance()
    {
        static BackManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

    void init() override;

private:
    static constexpr int OBJ_MAX = 2;
    OBJ2D objWork[OBJ_MAX];
};

void backUpdate(OBJ2D* obj);
