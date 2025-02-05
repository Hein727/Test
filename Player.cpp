#include "Player.h"
#include "Shot.h"
#include "SpriteData.h"
#include "Effect.h"
#include "Judge.h"

static constexpr float PLAYER_SPEED = 8.0f;
static constexpr float PLAYER_LIMIT_L = 0 + 64.0f;
static constexpr float PLAYER_LIMIT_R = 1280 - 64.0f;
static constexpr float PLAYER_LIMIT_U = 0 + 32.0f;
static constexpr float PLAYER_LIMIT_D = 720 - 32.0f;
static constexpr int DIRECTIONAL_INPUT_MASK = GameLib::input::PAD_UP | GameLib::input::PAD_DOWN | GameLib::input::PAD_LEFT | GameLib::input::PAD_RIGHT;    // 方向キーの入力取得用マスク

void playerMove(OBJ2D* obj)
{
    constexpr float R2 = 1.41421356f;   // ルート2の値
    constexpr float DIAGONAL_SPEED = PLAYER_SPEED / R2; // 斜めの速度
    static const VECTOR2 PLAYER_MOVEMENT_DIRECTIONS[] = {
        { 0, 0 },                             //  0   ----
        { 0, -PLAYER_SPEED },                 //  1   ---U
        { 0, PLAYER_SPEED },                  //  2   --D-
        { 0, 0 },                             //  3   --DU
        { -PLAYER_SPEED, 0 },                 //  4   -L--
        { -DIAGONAL_SPEED, -DIAGONAL_SPEED},  //  5   -L-U
        { -DIAGONAL_SPEED,  DIAGONAL_SPEED},  //  6   -LD-
        { -PLAYER_SPEED, 0 },                 //  7   _LDU
        {  PLAYER_SPEED, 0 },                 //  8   R---
        {  DIAGONAL_SPEED, -DIAGONAL_SPEED},  //  9   R--U
        {  DIAGONAL_SPEED,  DIAGONAL_SPEED},  // 10   R-D-
        {  PLAYER_SPEED, 0 },                 // 11   R-DU
        { 0, 0 },                             // 12   RL--
        { 0, -PLAYER_SPEED },                 // 13   RL-U
        { 0, PLAYER_SPEED },                  // 14   RLD-
        { 0, 0 },                             // 15   RLDU
    };
    obj->position += PLAYER_MOVEMENT_DIRECTIONS[obj->iWork[PlayerManager::PAD_STATE] & DIRECTIONAL_INPUT_MASK];
}

void playerUpdate(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->sprData = &sprPlayer;
        obj->position = { -64, 360 };

        obj->hSize = { 32/2, 16/2 };
        obj->judge = JUDGE_PLAYER;
        obj->hp = 8;
        obj->bomb = effectBomb;
        obj->score = 0;
        obj->state++;
        [[fallthrough]];

    case 1: // 出現
        obj->position.x += PLAYER_SPEED;

        if (obj->position.x > 640 ||
            (obj->position.x > 80 && obj->iWork[PlayerManager::PAD_STATE] & DIRECTIONAL_INPUT_MASK))
        {
            obj->state++;
        }
        break;

    case 2:
        // プレイヤー移動
        playerMove(obj);

        // 移動範囲チェック
        if (obj->position.x < PLAYER_LIMIT_L) obj->position.x = PLAYER_LIMIT_L;
        if (obj->position.x > PLAYER_LIMIT_R) obj->position.x = PLAYER_LIMIT_R;
        if (obj->position.y < PLAYER_LIMIT_U) obj->position.y = PLAYER_LIMIT_U;
        if (obj->position.y > PLAYER_LIMIT_D) obj->position.y = PLAYER_LIMIT_D;

        // ショット発射
        if (obj->iWork[PlayerManager::PAD_TRG] & GameLib::input::PAD_TRG1)
        {
            ShotManager::getInstance().searchSet(shotNormal, obj->position + VECTOR2(64, 0));
        }

        // ミサイル発射
        if (obj->iWork[PlayerManager::PAD_TRG] & GameLib::input::PAD_TRG2)
        {
            ShotManager::getInstance().searchSet(shotMissile, obj->position);
        }
        break;
    }
}

void PlayerManager::init()
{
    OBJ2DManager::init();
    searchSet(playerUpdate, { 640, 360 });
}

void PlayerManager::update()
{
    for (auto& player : *this)
    {
        // ↓SceneGame::updateに移動済み
        //player.iWork[PAD_STATE] = GameLib::input::STATE(0);
        //player.iWork[PAD_TRG] = GameLib::input::TRG(0);

        player.update();

        if (player.mover)
        {
            // ダメージタイマー
            if (player.damageTimer) player.damageTimer--;

            // ダメージを受けていたら赤くする（アルファは変更しない）
            player.color.x = 1.0f;
            player.color.y = player.damageTimer ? 0.0f : 1.0f;
            player.color.z = player.damageTimer ? 0.0f : 1.0f;

            // 自爆チェック
            if (player.hp == 0) setBomb(player);
        }
    }
}

bool PlayerManager::isAlive()
{
    for (auto& player : *this)
    {
        if (player.mover) return true;
    }
    return false;
}

//----------------------------------------------------------------

// オプション関連

static constexpr int POS_SAVE_MAX = 0x08 + 2;

struct OptionData
{
    VECTOR2 pos[POS_SAVE_MAX];
};

OptionData optionData[OptionManager::OBJ_MAX];

GameLib::SpriteData* sprOption[] = {
    &sprOption00,
    &sprOption01,
    &sprOption02,
    &sprOption01,
};

void optionNormal(OBJ2D* obj)
{
    enum IWorkIndex
    {
        PAD_STATE,
        PAD_TRG,
        PAD_OLD,
        PAD_NEW,
        READ,
        WRITE,
    };

    OBJ2D* parent = obj->parent;
    if (parent == nullptr || parent->mover == nullptr)
    {
        obj->clear();
        return;
    }

    OptionData* data = &optionData[obj->index];

    switch (obj->state)
    {
    case 0:
        for (int i = 0; i < POS_SAVE_MAX; i++)
        {
            data->pos[i] = parent->position;
        }
        obj->iWork[READ] = 2;
        obj->iWork[WRITE] = 0;
        obj->position = data->pos[obj->iWork[READ]];
        obj->state++;
        [[fallthrough]];

    case 1:
        // 移動
        obj->iWork[PAD_STATE] = obj->iWork[PAD_OLD];
        obj->iWork[PAD_OLD] = obj->iWork[PAD_NEW];
        obj->iWork[PAD_NEW] = parent->iWork[PAD_STATE] & DIRECTIONAL_INPUT_MASK;
        if (obj->iWork[PAD_STATE])
        {
            obj->position = data->pos[obj->iWork[READ]];
            obj->iWork[READ] = (obj->iWork[READ] + 1) % POS_SAVE_MAX;
        }
        if (obj->iWork[PAD_NEW])
        {
            data->pos[obj->iWork[WRITE]] = parent->position;
            obj->iWork[WRITE] = (obj->iWork[WRITE] + 1) % POS_SAVE_MAX;
        }
        // ショット発射
        obj->iWork[PAD_TRG] = parent->iWork[PAD_TRG];
        if (obj->iWork[PAD_TRG] & GameLib::input::PAD_TRG1) ShotManager::getInstance().searchSet(shotNormal, obj->position);
        if (obj->iWork[PAD_TRG] & GameLib::input::PAD_TRG2) ShotManager::getInstance().searchSet(shotMissile, obj->position);
        // アニメ
        obj->timer++;
        obj->sprData = sprOption[(obj->timer >> 2) & 0x03];
        break;
    }
}
