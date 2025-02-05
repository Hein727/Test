#include "Judge.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include "Shot.h"
#include "Scene.h"

class JudgeRect
{
public:
    JudgeRect(float l, float t, float r, float b)
    {
        left = l;
        top = t;
        right = r;
        bottom = b;
    }
    JudgeRect(const VECTOR2& position, const VECTOR2& hSize)
        :JudgeRect(position.x - hSize.x, position.y - hSize.y,
            position.x + hSize.x, position.y + hSize.y) {}

    bool isHit(const JudgeRect& other)
    {
        if (right < other.left) return false;
        if (left > other.right) return false;
        if (bottom < other.top) return false;
        if (top > other.bottom) return false;
        return true;
    }

private:
    float left, top, right, bottom;
};

// プロトタイプ宣言
void judgeSub(OBJ2DManager& manager1, OBJ2DManager& manager2);
void decHP(OBJ2D& item);

JudgeRect screenRect = {
    32, 32, SCREEN_WIDTH - 32, SCREEN_HEIGHT - 32, 
};

static constexpr int DAMAGE_TIME = 0x04;

void judge()
{
    // ショットVS敵キャラ
    judgeSub(ShotManager::getInstance(), EnemyManager::getInstance());

    // プレイヤーVS敵キャラ
    judgeSub(PlayerManager::getInstance(), EnemyManager::getInstance());
}

// Manager VS Manager
void judgeSub(OBJ2DManager& manager1, OBJ2DManager& manager2)
{
    for (auto& item1 : manager1)
    {
        if (!item1.mover) continue;

        JudgeRect rect1(item1.position, item1.hSize);
        // rect1があたり判定エリア外のとき、次のitem1へ
        if (rect1.isHit(screenRect) == false) continue;

        for (auto& item2 : manager2)
        {
            if (!item2.mover) continue;
            if ((item1.judge & item2.judge) == 0) continue;

            JudgeRect rect2(item2.position, item2.hSize);
            // rect2があたり判定エリア外のとき、次のitem2へ
            if (rect2.isHit(screenRect) == false) continue;

            if (rect1.isHit(rect2))
            {
                decHP(item1);
                decHP(item2);
                break;
            }
        }
    }
}

void decHP(OBJ2D& item)
{
    // 無敵チェック
    if (item.hp < 0) return;

    // ダメージタイマーチェック
    if (item.damageTimer) return;
    item.hp--;

    // ダメージタイマーを設定する
    item.damageTimer = DAMAGE_TIME;

    if (item.hp <= 0)
    {
        // スコア加算
        Stage::getInstance().addScore(item.score);
        setBomb(item);
    }
}

void setBomb(OBJ2D& item)
{
    EffectManager::getInstance().searchSet(item.bomb, item.position);
    item.clear();
}
