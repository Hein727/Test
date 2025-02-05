#include "UI.h"
#include "SpriteData.h"
#include "Player.h"

void UIMeter(OBJ2D* obj);
void UIFrame(OBJ2D* obj);

void UIManager::init()
{
    OBJ2DManager::init();

    objWork[0].mover = UIMeter;
    objWork[1].mover = UIFrame;
}

static constexpr float METER_SPEED = 4.0f;
static constexpr float METER_LENGTH = 512.0f;

void UIMeter(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->sprData = &sprMeter;
        obj->blendState = GameLib::Blender::BS_ADD;
        obj->color = { 1,1,1,0.8f };
        obj->position = { 16, 16 };
        obj->scale = { 0, 1 };
        obj->state++;
        [[fallthrough]];

    case 1:
        break;
    }

    OBJ2D* player = PlayerManager::getInstance().begin();
    float length = (player->mover) ? player->hp * 64.0f : 0.0f;

    float current = METER_LENGTH * obj->scale.x;

    if (current < length)
    {
        current += METER_SPEED;
        current = (std::min)(current, length);
    }
    if (current > length)
    {
        current -= METER_SPEED;
        current = (std::max)(current, length);
    }

    obj->scale.x = current / METER_LENGTH;
}

void UIFrame(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        obj->sprData = &sprFrame;
        obj->position = { 16, 16 };
        obj->state++;
        [[fallthrough]];

    case 1:
        break;
    }
}