#pragma once
#include "Obj2d.h"
#include <memory>

// �G�L���������f�[�^�i������X�e�[�W�X�N���v�g�ɂȂ�j

struct ScriptData
{
	virtual void execute() = 0;
	virtual ~ScriptData() = default;
};

struct StageScript
{
	int				time;		// �C�x���g��������
	std::unique_ptr<ScriptData> data;
};

//enum
//{
//	SCRIPT_ENEMY,
//	SCRIPT_END,
//	SCRIPT_BGM,
//	SCRIPT_DATA,
//};

struct ScriptEnemy : public ScriptData
{
	OBJ2D::MOVER mover;
	VECTOR2 position;
	ScriptEnemy(OBJ2D::MOVER m, VECTOR2 p) : mover(m), position(p) {}
	void execute() override;
};

struct ScriptBGM : public ScriptData
{
	int BGMno;
	ScriptBGM(int no) : BGMno(no) {}
	void execute() override;
};

// �X�N���v�g�}�N��
#define SET_ENEMY(time,y,mover)		{(time), std::make_unique<ScriptEnemy>(mover, VECTOR2{(1280 + 64), (y)})}
#define SET_BGM(time,index)			{(time), std::make_unique<ScriptBGM>(index)}
#define SET_END						{0, nullptr}

// Stage�N���X
class Stage
{
private:
	Stage() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
	Stage(const Stage&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
	Stage& operator=(const Stage&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
	static Stage& getInstance()
	{
		static Stage instance;
		return instance;
	}

	void init();
	void update();
	void draw();
	void addScore(int score);
	void drawScore();
	bool isAllClear();

private:
	int timer = 0;
	StageScript* pScript = nullptr;
	int playerScore = 0;
	int highScore = 57300;
	int state = 0;
	StageScript** ppScript = nullptr;
};
