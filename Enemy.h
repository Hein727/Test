#pragma once
#include "Obj2d.h"

class EnemyManager : public OBJ2DManager
{
private:
    EnemyManager() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
    EnemyManager(const EnemyManager&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
    EnemyManager& operator=(const EnemyManager&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

public:
    static EnemyManager& getInstance()
    {
        static EnemyManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }
    void update() override;
    bool isAlive();

private:
    static constexpr int OBJ_MAX = 100;
    OBJ2D objWork[OBJ_MAX];
};

// プロトタイプ宣言
void enemyShot(OBJ2D* obj);			// 敵の弾
void enemySin(OBJ2D* obj);			// サインカーブ
void enemyFall(OBJ2D* obj);			// 放物線
void enemyCannon(OBJ2D* obj);       // 砲台
void enemyHoming(OBJ2D* obj);       // ホーミング
void enemyAppear(OBJ2D* obj);       // 突然出現する敵
