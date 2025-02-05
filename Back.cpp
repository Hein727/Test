#include "Back.h"
#include "SpriteData.h"

void backUpdate(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->sprData = &sprBack;
        obj->state++;
        break;
    case 1:
        obj->position.x -= 4;

        // ƒXƒNƒ[ƒ‹ˆ—
        if (obj->position.x < -1280)
        {
            obj->position.x += 1280 * 2;
        }
        break;
    }
}

void BackManager::init()
{
    OBJ2DManager::init();
    searchSet(backUpdate, { 0, 0 });
    searchSet(backUpdate, { 1280, 0 });
}
