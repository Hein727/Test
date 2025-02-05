#include "Shot.h"
#include "SpriteData.h"
#include "Effect.h"
#include "AudioManager.h"

static constexpr float SHOT_SPEED = 16.0f;

// ショットの動作
void shotNormal(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        GameLib::sound::play(AudioManager::Sound::STAGE1, AudioManager::Stage1::SHOT);

        obj->hSize = { 64 / 2, 64 / 2 };
        obj->judge = JUDGE_SHOT;
        obj->sprData = &sprShot;
        obj->hp = 1;
        obj->bomb = nullptr;
        obj->score = 0;
        obj->state++;
        break;

    case 1:
        obj->position.x += SHOT_SPEED;
        if (obj->position.x > 1280 + 64)
        {
            obj->clear();
        }
        break;
    }
}

static constexpr float MISSILE_SPEED = -5.0f;
static constexpr float MISSILE_ACCEL = 0.2f;

// ミサイルの動作
void shotMissile(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        GameLib::sound::play(AudioManager::Sound::STAGE1, AudioManager::Stage1::MISSILE);

        obj->hSize = { 64 / 2, 64 / 2 };
        obj->judge = JUDGE_PLAYER;
        obj->sprData = &sprMissile;
        obj->velocity.x = MISSILE_SPEED;
        obj->hp = 1;
        obj->bomb = effectBomb;
        obj->score = 0;
        obj->state++;
        break;

    case 1:
        obj->velocity.x += MISSILE_ACCEL;
        obj->position.x += obj->velocity.x;
        if (obj->position.x > 1280 + 64)
        {
            obj->clear();
        }
        break;
    }
}
