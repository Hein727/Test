#pragma once
#include "Obj2d.h"

class UIManager : public OBJ2DManager
{
public:
    static UIManager& getInstance()
    {
        static UIManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

    void init() override;

private:
    UIManager() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    UIManager(const UIManager&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    UIManager& operator=(const UIManager&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

    static constexpr int OBJ_MAX = 2;
    OBJ2D objWork[OBJ_MAX];
};
