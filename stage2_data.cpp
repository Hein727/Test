#include "stage2_data.h"
#include "Enemy.h"
#include "AudioManager.h"

StageScript stage2Script[] = {
	SET_BGM(0, AudioManager::Music::IN_GAME),
	SET_ENEMY(400, 140, enemySin),
	SET_ENEMY(400, 220, enemySin),
	SET_ENEMY(400, 300, enemySin),

	SET_ENEMY(500, 420, enemySin),
	SET_ENEMY(500, 500, enemySin),
	SET_ENEMY(500, 580, enemySin),

	SET_ENEMY(700, 120, enemyFall),
	SET_ENEMY(725, 120, enemyFall),

	SET_ENEMY(950, 60, enemyFall),
	SET_ENEMY(975, 60, enemyFall),
	SET_ENEMY(1000, 60, enemyFall),

	SET_ENEMY(1200, 20, enemyFall),
	SET_ENEMY(1210, 60, enemyFall),
	SET_ENEMY(1220, 100, enemyFall),
	SET_ENEMY(1230, 140, enemyFall),
	SET_ENEMY(1240, 180, enemyFall),

	SET_ENEMY(1500, 280, enemyFall),
	SET_ENEMY(1525, 280, enemyFall),
	SET_ENEMY(1550, 280, enemyFall),

	SET_BGM(1550, AudioManager::Music::WARNING),
	SET_BGM(1700, AudioManager::Music::BOSS),

	SET_ENEMY(1700, 140, enemyCannon),
	SET_ENEMY(1750, 360, enemyCannon),
	SET_ENEMY(1800, 580, enemyCannon),

	SET_ENEMY(2000, 40, enemyFall),
	SET_ENEMY(2050, 680, enemyFall),

	SET_ENEMY(2200, 100, enemyFall),
	SET_ENEMY(2210, 60, enemyFall),
	SET_ENEMY(2220, 20, enemyFall),

	SET_ENEMY(2400, 620, enemyFall),
	SET_ENEMY(2410, 660, enemyFall),
	SET_ENEMY(2420, 700, enemyFall),

	SET_END								// 終了コード
};
