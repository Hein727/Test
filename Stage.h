#pragma once
#include "Obj2d.h"
#include <memory>

// 敵キャラ発生データ（いずれステージスクリプトになる）

struct ScriptData
{
	virtual void execute() = 0;
	virtual ~ScriptData() = default;
};

struct StageScript
{
	int				time;		// イベント発生時間
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

// スクリプトマクロ
#define SET_ENEMY(time,y,mover)		{(time), std::make_unique<ScriptEnemy>(mover, VECTOR2{(1280 + 64), (y)})}
#define SET_BGM(time,index)			{(time), std::make_unique<ScriptBGM>(index)}
#define SET_END						{0, nullptr}

// Stageクラス
class Stage
{
private:
	Stage() = default;  // デフォルトコンストラクタ。private にして、外部からのインスタンス化を防ぐ。
	Stage(const Stage&) = delete;  // コピーコンストラクタを削除。インスタンスのコピーを防ぐ。
	Stage& operator=(const Stage&) = delete;  // 代入演算子を削除。インスタンスの代入を防ぐ。

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
