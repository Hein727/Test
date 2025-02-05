#include "Enemy.h"
#include "Player.h"
#include "Effect.h"
#include "SpriteData.h"
#include "Utils.h"
#include "Judge.h"
#include "Scene.h"

// �G�L���������ݒ�f�[�^�\����
struct EnemyInitData
{
	GameLib::SpriteData*	sprData;	// �摜
	OBJ2D::ERASER			eraser;		// �����`�F�b�N
	VECTOR2					hSize;		// ������T�C�Y�i�̔����j
	int						judge;		// ������̎��
	int						hp;			// HP
	OBJ2D::MOVER			bomb;		// ��������
	int						score;		// �X�R�A
};

// �v���g�^�C�v�錾
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

			// �_���[�W���󂯂Ă�����Ԃ�����i�A���t�@�͕ύX���Ȃ��j
			enemy.color.x = 1.0f;
			enemy.color.y = enemy.damageTimer ? 0.0f : 1.0f;
			enemy.color.z = enemy.damageTimer ? 0.0f : 1.0f;

			// ����
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
// �w���p�[�֐�

// �G�L���������ݒ�֐�
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

// �v���C���[���W�擾
VECTOR2 getPlayerPos()
{
	OBJ2D* player = PlayerManager::getInstance().begin();
	return (player && player->mover) ? player->position : VECTOR2(640, 360);
}

//----------------------------------------------------------------
// �����`�F�b�N�i�ʏ�G�j

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
// �G�̒e

EnemyInitData initShot = {
	&sprEnemy, 
	eraseEnemy, 
	{ 32 / 2, 32 / 2 }, 
	JUDGE_PLAYER, 
	1, 
	nullptr, 
	100, 
};

static constexpr float ESHOT_SPEED = 8.0f;	// ���x

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
// �T�C���J�[�u

EnemyInitData initSin = {
	&sprEnemy, 
	eraseEnemy, 
	{ 48 / 2, 48 / 2 }, 
	JUDGE_ALL, 
	1, 
	effectBomb, 
	100, 
};

static constexpr float SIN_SPEEDX = -7.5f;		// X�������x
static constexpr float SIN_YOFS = 96.0f;		// �U��

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
		obj->fWork[YCenter] = obj->position.y;		// ��������Y���W�𒆐S���Ƃ���
		obj->position.y += SIN_YOFS;			// Y���W�͐U���̕��������炷
		obj->shotTimer = 60;

		obj->state++;
		[[fallthrough]];

	case 1:
		obj->velocity.y += (obj->fWork[YCenter] - obj->position.y) / 256;
		obj->position += obj->velocity;

		// �iCPPGame06A1�j1�b�Ԋu�Œe����
		if (--obj->shotTimer == 0)
		{
			EnemyManager::getInstance().searchSet(enemyShot, obj->position);
			obj->shotTimer = 60;
		}
		break;
	}
}




//----------------------------------------------------------------
// ������

EnemyInitData initFall = {
	&sprEnemy, 
	eraseEnemy, 
	{ 48 / 2, 48 / 2 }, 
	JUDGE_ALL, 
	1, 
	effectBomb, 
	100, 
};

static constexpr float FALL_SPEEDX = -24.0f;	// X���������x
static constexpr float FALL_ACCX = 0.25f;		// X���������x
static constexpr float FALL_SPEEDY = 3.5f;		// Y�������x
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
// �C��

EnemyInitData initCannon = {
	&sprEnemy, 
	eraseEnemy, 
	{ 96 / 2, 96 / 2 }, 
	JUDGE_ALL, 
	30, 
	effectBomb2, 
	1000, 
};

static constexpr float CANNON_SPEED1 = -8.0f;					// �o�����̑��x
static constexpr float CANNON_SPEED2 = -4.0f;					// �ړ����̑��x
static constexpr float CANNON_WAIT_POSX = SCREEN_WIDTH - 80.0f;	// �ꎞ��~����X���W
static constexpr int CANNON_WAIT_TIME = 850;					// �ꎞ��~�̎���
static constexpr int CANNON_SHOT_INTERVAL = 8;					// �e�����Ԋu

void enemyCannon(OBJ2D *obj)
{
	switch (obj->state)
	{
	case 0:	// �����ݒ�
		enemyInit(obj, &initCannon);
		obj->scale = { 2, 2 };
		obj->velocity = VECTOR2(CANNON_SPEED1, 0);
		obj->shotTimer = CANNON_SHOT_INTERVAL;
		obj->state++;
		[[fallthrough]];

	case 1:	// �O�i��
		obj->position += obj->velocity;
		if (obj->position.x < CANNON_WAIT_POSX)
		{
			obj->timer = 850;
			obj->state++;
		}
		break;

	case 2:	// ��~��
		if (--obj->timer == 0)
		{
			obj->velocity = VECTOR2(CANNON_SPEED2, 0);
			obj->state++;
		}
		break;

	case 3:	// �đO�i��
		obj->position += obj->velocity;
		break;
	}

	// �e����
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
// �z�[�~���O�iCPPGame06S1�j

EnemyInitData initHoming = {
	&sprEnemy, 
	nullptr, 
	{ 48 / 2, 48 / 2 }, 
	JUDGE_ALL, 
	1, 
	effectBomb, 
	100, 
};

static constexpr float HOMING_SPEED = 8.0f;		// �o�����̑��x
static constexpr float HOMING_ROTATE = 0.025f;	// ��]�p�x

void enemyHoming(OBJ2D* obj)
{
    // �i�쐬���邱�Ɓj
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

    case 2: // �z�[�~���O��

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
// ��ʏ�ɓˑR�o������G

EnemyInitData initAppear = {
	&sprEnemy, 
	eraseEnemy, 
	{ 48 / 2, 48 / 2 }, 
	0, 
	1, 
	effectBomb, 
	100, 
};

static constexpr float APP_ALPHA = 0.008f;	// �A���t�@���Z�l
static constexpr float APP_SPEED = 12.0f;			// �X�s�[�h
static constexpr float APP_ROTATE = 0.5f;			// ��]���x

void enemyAppear(OBJ2D *obj)
{
	switch (obj->state)
	{
	case 0: // �����ݒ�
		enemyInit(obj, &initAppear);
		obj->color.w = 0.0f;
		obj->position = VECTOR2(static_cast<float>(rand() % 1280), static_cast<float>(rand() % 720));
		obj->blendState = GameLib::Blender::BS_ALPHA;
		obj->state++;
		[[fallthrough]];

	case 1: // �p������
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

	case 2: // �v���C���[�Ɍ������Ē��i����
		obj->position += obj->velocity;
		obj->rotation += APP_ROTATE;
		break;
	}
}
