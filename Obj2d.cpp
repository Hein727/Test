#include "Obj2d.h"

void OBJ2D::update()
{
    if (mover) mover(this);
    if (eraser && eraser(this))
    {
        clear();
    }
}

void OBJ2D::draw()
{
    if (sprData)
    {
        auto oldState = GameLib::getBlendMode();
        GameLib::setBlendMode(blendState);
        sprData->draw(position, scale, rotation, color);
        GameLib::setBlendMode(oldState);
    }
}

//----------------------------------------------------------------
// OBJ2DManager

void OBJ2DManager::init()
{
    for (auto& obj : *this) obj.clear();
}

void OBJ2DManager::update()
{
    for (auto& obj : *this) obj.update();
}

void OBJ2DManager::draw()
{
    for (auto& obj : *this) obj.draw();
}

OBJ2D* OBJ2DManager::searchSet(OBJ2D::MOVER mover, const VECTOR2& position)
{
    for (auto& obj : *this)
    {
        if (obj.mover != nullptr) { continue; }

        obj.clear();
        obj.mover = mover;
        obj.position = position;

        return &obj;
    }

    return nullptr;
}
