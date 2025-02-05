#pragma once

#include "./GameLib/game_lib.h"
#include "./GameLib/obj2d_data.h"

inline constexpr int JUDGE_PLAYER = 0x01;
inline constexpr int JUDGE_SHOT = 0x02;
inline constexpr int JUDGE_ALL = (JUDGE_PLAYER | JUDGE_SHOT);

class OBJ2D
{
public:
    //typedef void(*MOVER)(OBJ2D* obj);
    //typedef bool(*ERASER)(OBJ2D* obj);
    using MOVER = void(*)(OBJ2D* obj);
    using ERASER = bool(*)(OBJ2D* obj);

    OBJ2D() { init(); }

    void init()
    {
        sprData = nullptr;
        position = {};
        scale = { 1,1 };
        rotation = 0.0f;
        color = { 1,1,1,1 };
        blendState = GameLib::Blender::BLEND_STATE::BS_ALPHA;
        state = 0;
        velocity = {};
        timer = 0;
        mover = nullptr;
        eraser = nullptr;
        index = 0;
        parent = nullptr;

        for (auto& i : iWork) { i = 0; }
        for (auto& f : fWork) { f = 0.0f; }
        for (auto& v : vWork) { v = {}; }

        hSize = {};
        judge = 0;
        hp = 0;
        bomb = nullptr;
        score = 0;
        damageTimer = 0;
    }
    void clear() { init(); }

    void update();
    void draw();

    int iWork[8];
    float fWork[8];
    VECTOR2 vWork[4];

    GameLib::SpriteData* sprData;
    VECTOR2 position;
    VECTOR2 scale;
    float rotation;
    VECTOR4 color;
    GameLib::Blender::BLEND_STATE blendState;
    int state;
    VECTOR2 velocity;
    int timer;
    int shotTimer;
    MOVER mover;
    ERASER eraser;
    int index;
    OBJ2D* parent;
    VECTOR2 hSize;
    int judge;
    int hp;
    MOVER bomb;
    int score;
    int damageTimer;

    // 必要に乗じてメンバ追加（init関数で初期設定を忘れないこと）

};

class OBJ2DManager
{
public:
    virtual OBJ2D* begin() = 0;
    virtual OBJ2D* end() = 0;

    virtual void init();
    virtual void update();
    void draw();

    /// <summary>
    /// OBJ2Dを生成する
    /// </summary>
    /// <param name="mover">移動アルゴリズム（関数ポインタ）</param>
    /// <param name="position">位置</param>
    /// <returns>生成したOBJ2Dのアドレス</returns>
    OBJ2D* searchSet(OBJ2D::MOVER mover, const VECTOR2& position);
};