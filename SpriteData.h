#pragma once
#include "GameLib/game_lib.h"
#include "GameLib/obj2d_data.h"

enum TEXNO
{
    BACK00, 
    SPR000, 
    MISC, 
};

struct SpriteUpperLeft : public GameLib::SpriteData
{
    SpriteUpperLeft(int texno, float left, float top, float width, float height)
    {
        this->texNo = texno;
        this->left = left;
        this->top = top;
        this->width = width;
        this->height = height;
        this->centerX = 0;
        this->centerY = 0;
    }
};

struct SpriteCenter : public GameLib::SpriteData
{
    SpriteCenter(int texno, float left, float top, float width, float height)
    {
        this->texNo = texno;
        this->left = left;
        this->top = top;
        this->width = width;
        this->height = height;
        this->centerX = width / 2;
        this->centerY = height / 2;
    }
};

struct SpriteMiddleRight : public GameLib::SpriteData
{
    SpriteMiddleRight(int texno, float left, float top, float width, float height)
    {
        this->texNo = texno;
        this->left = left;
        this->top = top;
        this->width = width;
        this->height = height;
        this->centerX = width;
        this->centerY = height / 2;
    }
};


extern GameLib::LoadTexture loadTexture[];

extern SpriteUpperLeft sprBack;
extern SpriteCenter sprPlayer;

extern SpriteCenter sprShot;
extern SpriteCenter sprMissile;

extern SpriteMiddleRight sprOption00;
extern SpriteMiddleRight sprOption01;
extern SpriteMiddleRight sprOption02;

extern SpriteCenter sprEnemy;
extern SpriteCenter sprEnemyShot00;
extern SpriteCenter sprEnemyShot01;

extern SpriteCenter sprBomb00;
extern SpriteCenter sprBomb01;
extern SpriteCenter sprBomb02;
extern SpriteCenter sprBomb03;
extern SpriteCenter sprBomb04;

extern SpriteUpperLeft sprMeter;
extern SpriteUpperLeft sprFrame;
