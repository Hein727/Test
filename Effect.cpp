#include "Effect.h"
#include "SpriteData.h"
#include "AudioManager.h"

GameLib::SpriteData* sprBomb[] = {
    &sprBomb00, 
    &sprBomb01, 
    &sprBomb02, 
    &sprBomb03, 
    &sprBomb04, 
    nullptr,    // I—¹ƒtƒ‰ƒO
};

void effectBomb(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        GameLib::sound::play(AudioManager::Sound::STAGE1, AudioManager::Stage1::BOMB);

        obj->state++;
        [[fallthrough]];

    case 1:
        obj->timer++;
        obj->sprData = sprBomb[obj->timer >> 2];
        if (!obj->sprData) obj->clear();
        break;
    }
}

void effectBomb2(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->scale = { 4, 4 };
        obj->state++;
        [[fallthrough]];

    case 1:
        obj->timer++;
        obj->sprData = sprBomb[obj->timer >> 3];
        if (!obj->sprData) obj->clear();
        break;
    }
}
