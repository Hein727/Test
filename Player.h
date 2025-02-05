#pragma once
#include "Obj2d.h"

class PlayerManager : public OBJ2DManager
{
private:
    PlayerManager() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    PlayerManager(const PlayerManager&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    PlayerManager& operator=(const PlayerManager&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    enum IWorkIndex
    {
        PAD_STATE,
        PAD_TRG,
    };

    static PlayerManager& getInstance()
    {
        static PlayerManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

    void init() override;
    void update() override;
    bool isAlive();

private:
    static constexpr int OBJ_MAX = 1;
    OBJ2D objWork[OBJ_MAX];
};

void playerMove(OBJ2D* obj);
void playerUpdate(OBJ2D* obj);

//----------------------------------------------------------------

class OptionManager : public OBJ2DManager
{
private:
    OptionManager() = default;
    OptionManager(const OptionManager&) = delete;
    OptionManager& operator=(const OptionManager&) = delete;

public:
    static OptionManager& getInstance()
    {
        static OptionManager instance;
        return instance;
    }

    OBJ2D* begin() { return &objWork[0]; }
    OBJ2D* end() { return &objWork[OBJ_MAX]; }

    static constexpr int OBJ_MAX = 4;

private:
    OBJ2D objWork[OBJ_MAX];
};

void optionNormal(OBJ2D* obj);
