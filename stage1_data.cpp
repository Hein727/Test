#include "stage1_data.h"
#include "Enemy.h"
#include "AudioManager.h"

StageScript stage1Script[] = {
	SET_BGM(0, AudioManager::Music::IN_GAME),
	SET_ENEMY(60, 0, enemyAppear),
	SET_ENEMY(80, 0, enemyAppear),
	SET_ENEMY(100, 0, enemyAppear),
	SET_ENEMY(120, 0, enemyAppear),
	SET_ENEMY(140, 0, enemyAppear),
	SET_ENEMY(160, 0, enemyAppear),
	SET_ENEMY(180, 0, enemyAppear),
	SET_ENEMY(200, 0, enemyAppear),
	SET_ENEMY(220, 0, enemyAppear),
	SET_ENEMY(240, 0, enemyAppear),

	SET_ENEMY(400, 140, enemySin),
	SET_ENEMY(500, 580, enemySin),

	SET_ENEMY(700, 140, enemySin),
	SET_ENEMY(700, 220, enemySin),
	SET_ENEMY(700, 300, enemySin),


	SET_ENEMY(800, 420, enemySin),
	SET_ENEMY(800, 500, enemySin),
	SET_ENEMY(800, 580, enemySin),

	SET_ENEMY(1100, 140, enemySin),
	SET_ENEMY(1150, 580, enemySin),

	SET_ENEMY(1300, 140, enemySin),
	SET_ENEMY(1300, 220, enemySin),
	SET_ENEMY(1300, 300, enemySin),

	SET_ENEMY(1350, 420, enemySin),
	SET_ENEMY(1350, 500, enemySin),
	SET_ENEMY(1350, 580, enemySin),

	SET_ENEMY(1550, 10, enemyFall),
	SET_ENEMY(1575, 10, enemyFall),
	SET_ENEMY(1600, 10, enemyFall),

	SET_ENEMY(1750, 710, enemyFall),
	SET_ENEMY(1775, 710, enemyFall),
	SET_ENEMY(1800, 710, enemyFall),

	SET_BGM(1900, AudioManager::Music::WARNING),
	SET_BGM(2100, AudioManager::Music::BOSS),

	SET_ENEMY(2100, 360, enemyCannon),

	SET_ENEMY(2400, 80, enemyHoming), 
	SET_ENEMY(2420, 80, enemyHoming), 
	SET_ENEMY(2440, 80, enemyHoming), 

	SET_END								// 終了コード
};
