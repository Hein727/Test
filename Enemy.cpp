#include "Enemy.h"
#include "Player.h"
#include "Effect.h"
#include "SpriteData.h"
#include "Utils.h"
#include "Judge.h"
#include "Scene.h"

// 敵キャラ初期設定データ構造体
struct EnemyInitData
{
	GameLib::SpriteData*	sprData;	// 画像
	OBJ2D::ERASER			eraser;		// 消去チェック
	VECTOR2					hSize;		// あたりサイズ（の半分）
	int						judge;		// あたりの種類
	int						hp;			// HP
	OBJ2D::MOVER			bomb;		// 爆発処理
	int						score;		// スコア
};

// プロトタイプ宣言
void enemyInit(OBJ2D* obj, EnemyInitData* initData);
VECTOR2 getPlayerPos();
bool eraseEnemy(OBJ2D* obj);

//----------------------------------------------------------------
// EnemyManager
void EnemyManager::update()
{
	for (auto& enemy : *this)
	{
		enemy.update();

		if (enemy.mover)
		{
			if (enemy.damageTimer) enemy.damageTimer--;

			// ダメージを受けていたら赤くする（アルファは変更しない）
			enemy.color.x = 1.0f;
			enemy.color.y = enemy.damageTimer ? 0.0f : 1.0f;
			enemy.color.z = enemy.damageTimer ? 0.0f : 1.0f;

			// 自爆
			if (enemy.hp == 0) setBomb(enemy);
		}
	}
}

bool EnemyManager::isAlive()
{
	for (auto& enemy : *this)
	{
		if (enemy.mover) return true;
	}
	return false;
}

//----------------------------------------------------------------
// ヘルパー関数

// 敵キャラ初期設定関数
void enemyInit(OBJ2D* obj, EnemyInitData* initData)
{
	obj->sprData = initData->sprData;
	obj->eraser = initData->eraser;
	obj->hSize = initData->hSize;
	obj->judge = initData->judge;
	obj->hp = initData->hp;
	obj->bomb = initData->bomb;
	obj->score = initData->score;
}

// プレイヤー座標取得
VECTOR2 getPlayerPos()
{
	OBJ2D* player = PlayerManager::getInstance().begin();
	return (player && player->mover) ? player->position : VECTOR2(640, 360);
}

//----------------------------------------------------------------
// 消去チェック（通常敵）

static constexpr int ENEMY_MARGIN = 128;
static constexpr int ENEMY_SCREEN_L = 0 - ENEMY_MARGIN;
static constexpr int ENEMY_SCREEN_R = SCREEN_WIDTH + ENEMY_MARGIN;
static constexpr int ENEMY_SCREEN_U = 0 - ENEMY_MARGIN;
static constexpr int ENEMY_SCREEN_D = SCREEN_HEIGHT + ENEMY_MARGIN;

bool eraseEnemy(OBJ2D* obj)
{
	if (obj->position.x < ENEMY_SCREEN_L ||
		obj->position.x > ENEMY_SCREEN_R ||
		obj->position.y < ENEMY_SCREEN_U ||
		obj->position.y > ENEMY_SCREEN_D)
	{
		return true;
	}

	return false;
}




//----------------------------------------------------------------
// 敵の弾

EnemyInitData initShot = {
	&sprEnemy, 
	eraseEnemy, 
	{ 32 / 2, 32 / 2 }, 
	JUDGE_PLAYER, 
	1, 
	nullptr, 
	100, 
};

static constexpr float ESHOT_SPEED = 8.0f;	// 速度

void enemyShot(OBJ2D* obj)
{
	VECTOR2	dst;
	float dist;

	switch (obj->state)
	{
	case 0:
		enemyInit(obj, &initShot);
		dst = getPlayerPos() - obj->position;
		dist = sqrtf(dst.x * dst.x + dst.y * dst.y);
		obj->velocity = ESHOT_SPEED * dst / dist;
		obj->state++;
		[[fallthrough]];

	case 1:
		obj->timer++;
		obj->sprData = (obj->timer & 0x04) ? &sprEnemyShot00 : &sprEnemyShot01;
		obj->position += obj->velocity;
		break;
	}
}




//----------------------------------------------------------------
// サインカーブ

EnemyInitData initSin = {
	&sprEnemy, 
	eraseEnemy, 
	{ 48 / 2, 48 / 2 }, 
	JUDGE_ALL, 
	1, 
	effectBomb, 
	100, 
};

static constexpr float SIN_SPEEDX = -7.5f;		// X方向速度
static constexpr float SIN_YOFS = 96.0f;		// 振幅

void enemySin(OBJ2D* obj)
{
	enum FWorkIndex
	{
		YCenter,
	};

	switch (obj->state)
	{
	case 0:
		enemyInit(obj, &initSin);
		obj->velocity.x = SIN_SPEEDX;
		obj->fWork[YCenter] = obj->position.y;		// 発生時のY座標を中心軸とする
		obj->position.y += SIN_YOFS;			// Y座標は振幅の分だけずらす
		obj->shotTimer = 60;

		obj->state++;
		[[fallthrough]];

	case 1:
		obj->velocity.y += (obj->fWork[YCenter] - obj->position.y) / 256;
		obj->position += obj->velocity;

		// （CPPGame06A1）1秒間隔で弾撃ち
		if (--obj->shotTimer == 0)
		{
			EnemyManager::getInstance().searchSet(enemyShot, obj->position);
			obj->shotTimer = 60;
		}
		break;
	}
}




//----------------------------------------------------------------
// 放物線

EnemyInitData initFall = {
	&sprEnemy, 
	eraseEnemy, 
	{ 48 / 2, 48 / 2 }, 
	JUDGE_ALL, 
	1, 
	effectBomb, 
	100, 
};

static constexpr float FALL_SPEEDX = -24.0f;	// X方向初速度
static constexpr float FALL_ACCX = 0.25f;		// X方向加速度
static constexpr float FALL_SPEEDY = 3.5f;		// Y方向速度
static constexpr int FALL_SHOT_INTERVAL = 15;

void enemyFall(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		enemyInit(obj, &initFall);
		obj->velocity = VECTOR2(FALL_SPEEDX, FALL_SPEEDY);
		if (obj->position.y > 360) obj->velocity.y = -obj->velocity.y;
		obj->shotTimer = FALL_SHOT_INTERVAL;
		obj->state++;
		[[fallthrough]];

	case 1:
		obj->velocity.x += FALL_ACCX;
		obj->position += obj->velocity;

		if (obj->velocity.x > 0)
		{
			if (--obj->shotTimer == 0)
			{
				EnemyManager::getInstance().searchSet(enemyShot, obj->position);
				obj->shotTimer = FALL_SHOT_INTERVAL;
			}
		}

		break;
	}
}




//----------------------------------------------------------------
// 砲台

EnemyInitData initCannon = {
	&sprEnemy, 
	eraseEnemy, 
	{ 96 / 2, 96 / 2 }, 
	JUDGE_ALL, 
	30, 
	effectBomb2, 
	1000, 
};

static constexpr float CANNON_SPEED1 = -8.0f;					// 出現時の速度
static constexpr float CANNON_SPEED2 = -4.0f;					// 移動時の速度
static constexpr float CANNON_WAIT_POSX = SCREEN_WIDTH - 80.0f;	// 一時停止するX座標
static constexpr int CANNON_WAIT_TIME = 850;					// 一時停止の時間
static constexpr int CANNON_SHOT_INTERVAL = 8;					// 弾を撃つ間隔

void enemyCannon(OBJ2D *obj)
{
	switch (obj->state)
	{
	case 0:	// 初期設定
		enemyInit(obj, &initCannon);
		obj->scale = { 2, 2 };
		obj->velocity = VECTOR2(CANNON_SPEED1, 0);
		obj->shotTimer = CANNON_SHOT_INTERVAL;
		obj->state++;
		[[fallthrough]];

	case 1:	// 前進中
		obj->position += obj->velocity;
		if (obj->position.x < CANNON_WAIT_POSX)
		{
			obj->timer = 850;
			obj->state++;
		}
		break;

	case 2:	// 停止中
		if (--obj->timer == 0)
		{
			obj->velocity = VECTOR2(CANNON_SPEED2, 0);
			obj->state++;
		}
		break;

	case 3:	// 再前進中
		obj->position += obj->velocity;
		break;
	}

	// 弾発射
	if (obj->state == 2 || obj->state == 3)
	{
		if (--obj->shotTimer == 0)
		{
			EnemyManager::getInstance().searchSet(enemyShot, obj->position);
			obj->shotTimer = CANNON_SHOT_INTERVAL;
		}
	}

	obj->color = obj->damageTimer ? VECTOR4(1, 0, 0, 1) : VECTOR4(1, 1, 1, 1);
}




//----------------------------------------------------------------
// ホーミング（CPPGame06S1）

EnemyInitData initHoming = {
	&sprEnemy, 
	nullptr, 
	{ 48 / 2, 48 / 2 }, 
	JUDGE_ALL, 
	1, 
	effectBomb, 
	100, 
};

static constexpr float HOMING_SPEED = 8.0f;		// 出現時の速度
static constexpr float HOMING_ROTATE = 0.025f;	// 回転角度

void enemyHoming(OBJ2D* obj)
{
    // （作成すること）
    switch (obj->state)
    {
    case 0:
        enemyInit(obj, &initHoming);
        obj->scale = { -1, 1 };
        obj->rotation = DirectX::XM_PI;
        obj->timer = 60;
        obj->state++;
        [[fallthrough]];

    case 1:
        --obj->timer;
        if (obj->timer == 0)
        {
            obj->timer = 60 * 10;
            obj->state++;
        }
        break;

    case 2: // ホーミング中

    {
        VECTOR2 dir = vec2Normalize(obj->velocity);
        VECTOR2 toPlayer = PlayerManager::getInstance().begin()->position - obj->position;
        toPlayer = vec2Normalize(toPlayer);

        float cross = dir.x * toPlayer.y - dir.y * toPlayer.x;

        float dot = dir.x * toPlayer.x + dir.y * toPlayer.y;
        dot = std::clamp<float>(dot, -1.0f, 1.0f);

        float theta = acosf(dot);
        float add = theta > HOMING_ROTATE ? HOMING_ROTATE : theta;

        if (cross > 0)
        {
            obj->rotation += add;
        }
        if (cross < 0)
        {
            obj->rotation -= add;
        }
    }


	    --obj->timer;
	    if (obj->timer == 0)
	    {
	        obj->eraser = eraseEnemy;
	        obj->state++;
	    }
	    break;

    case 3:
        break;
    }

    obj->velocity = {
        cosf(obj->rotation) * HOMING_SPEED,
        sinf(obj->rotation) * HOMING_SPEED
    };
    obj->position += obj->velocity;
}




//----------------------------------------------------------------
// 画面上に突然出現する敵

EnemyInitData initAppear = {
	&sprEnemy, 
	eraseEnemy, 
	{ 48 / 2, 48 / 2 }, 
	0, 
	1, 
	effectBomb, 
	100, 
};

static constexpr float APP_ALPHA = 0.008f;	// アルファ加算値
static constexpr float APP_SPEED = 12.0f;			// スピード
static constexpr float APP_ROTATE = 0.5f;			// 回転速度

void enemyAppear(OBJ2D *obj)
{
	switch (obj->state)
	{
	case 0: // 初期設定
		enemyInit(obj, &initAppear);
		obj->color.w = 0.0f;
		obj->position = VECTOR2(static_cast<float>(rand() % 1280), static_cast<float>(rand() % 720));
		obj->blendState = GameLib::Blender::BS_ALPHA;
		obj->state++;
		[[fallthrough]];

	case 1: // 姿を現す
		obj->color.w += APP_ALPHA;
		if (obj->color.w >= 1.0f)
		{
			obj->judge = JUDGE_ALL;
			obj->color.w = 1.0f;
			VECTOR2 toPlayer = getPlayerPos() - obj->position;
			float length = sqrtf(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
			obj->velocity = toPlayer / length * APP_SPEED;
			obj->state++;
		}
		obj->rotation += APP_ROTATE;
		break;

	case 2: // プレイヤーに向かって直進する
		obj->position += obj->velocity;
		obj->rotation += APP_ROTATE;
		break;
	}
}
