#include "SceneGame.h"
#include <fstream>
#include <iomanip>
#include "./GameLib/game_lib.h"
#include "Stage.h"
#include "Command.h"
#include "Player.h"
#include "SceneTitle.h"
#include "SceneOver.h"
#include "SceneClear.h"
#include "AudioManager.h"

class Pause
{
public:
    void init();
    int operator()();
    void draw();

private:
    int			    state;			// ポーズ状態
    CommandParser	bombParser;		// 自爆コマンド
    CommandParser	powerUpParser;	// ????コマンド
};

static Pause pause;

void SceneGame::init()
{
	srand(0);
    Stage::getInstance().init();

	pause.init();

	state = 0;
	timer = 0;
	frame = 0;
}

void SceneGame::update()
{
    using namespace GameLib::input;

    // ソフトリセット
	if (STATE(0) & PAD_SELECT && TRG(0) & PAD_START) { setScene(SceneTitle::getInstance()); return; }

    // ポーズ
	if (pause()) return;

	// プレイヤーの入力
	OBJ2D* player = PlayerManager::getInstance().begin();
	if (player)
	{
		player->iWork[PlayerManager::PAD_TRG] = TRG(0);
		player->iWork[PlayerManager::PAD_STATE] = STATE(0);
	}

    Stage::getInstance().update();

	// シーン切り替えチェック
	switch (state)
	{
	case 0:
		if (PlayerManager::getInstance().isAlive() == false) { state = 1; }
		if (Stage::getInstance().isAllClear()) { state = 2; }
		break;

	case 1:
		timer++;
		if (timer > 60 * 2) { setScene(SceneOver::getInstance()); return; }
		break;

	case 2:
		timer++;
		if (timer > 60 * 2) { setScene(SceneClear::getInstance()); return; }
		break;
	}
}

void SceneGame::draw()
{
    // 画面をクリア
    GameLib::clear(0, 0, 0);

    Stage::getInstance().draw();

	pause.draw();
}

//----------------------------------------------------------------

// 隠しコマンド
namespace {
	static constexpr int COMMAND_INTERVAL = 16;
	using namespace GameLib::input;

	CommandData commandPowerUp[] = {
		{ PAD_UP,       COMMAND_INTERVAL },	// 上
		{ PAD_UP,       COMMAND_INTERVAL }, // 上
		{ PAD_DOWN,     COMMAND_INTERVAL }, // 下
		{ PAD_DOWN,     COMMAND_INTERVAL },	// 下
		{ PAD_LEFT,     COMMAND_INTERVAL },	// 左
		{ PAD_RIGHT,    COMMAND_INTERVAL },	// 右
		{ PAD_LEFT,     COMMAND_INTERVAL },	// 左
		{ PAD_RIGHT,    COMMAND_INTERVAL },	// 右
		{ PAD_TRG1,     COMMAND_INTERVAL },	// A
		{ PAD_TRG2,     0 },				// B（0：終了コード）
	};

	// 自爆コマンド
	CommandData commandBomb[] = {
		{ PAD_TRG1,     COMMAND_INTERVAL },	// A
		{ PAD_TRG1,     COMMAND_INTERVAL }, // A
		{ PAD_TRG1,     0 },				// A（0：終了コード）
	};
}

void Pause::init()
{
	state = 0;
}

int Pause::operator()()
{
	using namespace GameLib::input;

	switch (state)
	{
	case 0:	// 通常時
		if (TRG(0) & PAD_START)
		{
			state = 1;
			GameLib::sound::play(AudioManager::Sound::SYSTEM, AudioManager::System::START);
			bombParser.init(commandBomb);
			powerUpParser.init(commandPowerUp);
		}
		break;

	case 1:	// ポーズ時
		if (TRG(0) & PAD_START)
		{
			state = 0;
			GameLib::sound::play(AudioManager::Sound::SYSTEM, AudioManager::System::START);
			break;
		}
		if (bombParser(TRG(0)))
		{
			auto player = PlayerManager::getInstance().begin();
			player->hp = 0;
		}
		if (powerUpParser(TRG(0)))
		{
			auto parent = PlayerManager::getInstance().begin();
			if (parent->mover)
			{
				parent->hp = 8;

				int index = 0;
				for (auto& option : OptionManager::getInstance())
				{
					if (option.mover) continue;
					option.clear();
					option.mover = (OBJ2D::MOVER)optionNormal;
					option.parent = parent;
					option.index = index++;
					parent = &option;
				}
				OptionManager::getInstance().update();
			}
		}
		break;
	}

	return state;
}

void Pause::draw()
{
	if (state)
	{
		GameLib::font::textOut(4, "PAUSE", { 640, 360 }, { 3, 3 },
			{ 1, 1, 1, 1 }, GameLib::TEXT_ALIGN::MIDDLE);
	}
}

