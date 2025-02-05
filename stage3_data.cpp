#include "stage3_data.h"
#include "Enemy.h"
#include "AudioManager.h"

StageScript stage3Script[] = {
	SET_BGM(0, AudioManager::Music::IN_GAME),
	SET_ENEMY(400, 40, enemyFall),
	SET_ENEMY(425, 40, enemyFall),
	SET_ENEMY(450, 40, enemyFall),
	SET_ENEMY(475, 40, enemyFall),
	SET_ENEMY(500, 40, enemyFall),

	SET_ENEMY(550, 680, enemyFall),
	SET_ENEMY(575, 680, enemyFall),
	SET_ENEMY(600, 680, enemyFall),
	SET_ENEMY(625, 680, enemyFall),
	SET_ENEMY(650, 680, enemyFall),

	SET_ENEMY(700, 360, enemyCannon),

	SET_ENEMY(850, 40, enemyFall),
	SET_ENEMY(875, 40, enemyFall),
	SET_ENEMY(900, 40, enemyFall),

	SET_ENEMY(950, 680, enemyFall),
	SET_ENEMY(975, 680, enemyFall),
	SET_ENEMY(1000, 680, enemyFall),

	SET_ENEMY(1200, 140, enemySin),
	SET_ENEMY(1200, 220, enemySin),
	SET_ENEMY(1200, 300, enemySin),

	SET_ENEMY(1300, 420, enemySin),
	SET_ENEMY(1300, 500, enemySin),
	SET_ENEMY(1300, 580, enemySin),

	SET_ENEMY(1400, 40, enemyFall),
	SET_ENEMY(1425, 40, enemyFall),
	SET_ENEMY(1450, 40, enemyFall),
	SET_ENEMY(1475, 40, enemyFall),
	SET_ENEMY(1500, 40, enemyFall),
	SET_ENEMY(1525, 40, enemyFall),
	SET_ENEMY(1550, 40, enemyFall),
	SET_ENEMY(1575, 40, enemyFall),

	SET_ENEMY(1600, 600, enemyCannon),

	SET_ENEMY(1700, 380, enemyFall),
	SET_ENEMY(1725, 380, enemyFall),
	SET_ENEMY(1750, 380, enemyFall),
	SET_ENEMY(1775, 380, enemyFall),
	SET_ENEMY(1800, 380, enemyFall),
	SET_ENEMY(1825, 380, enemyFall),
	SET_ENEMY(1850, 380, enemyFall),
	SET_ENEMY(1875, 380, enemyFall),

	SET_BGM(1700, AudioManager::Music::WARNING),
	SET_BGM(1900, AudioManager::Music::BOSS),

	SET_ENEMY(1900, 480, enemyCannon),

    SET_ENEMY(2200, 120, enemyCannon),
    SET_ENEMY(2250, 240, enemyCannon),
    SET_ENEMY(2300, 300, enemyCannon),
    SET_ENEMY(2300, 420, enemyCannon),
    SET_ENEMY(2350, 540, enemyCannon),
    SET_ENEMY(2350, 660, enemyCannon),

	SET_ENEMY(2400, 80, enemyFall),
	SET_ENEMY(2425, 80, enemyFall),
	SET_ENEMY(2450, 80, enemyFall),
	SET_ENEMY(2475, 80, enemyFall),
	SET_ENEMY(2500, 80, enemyFall),

	SET_END								// 終了コード
};
