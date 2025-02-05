#include "Stage.h"
#include <sstream>
#include <iomanip>
#include "stage1_data.h"
#include "stage2_data.h"
#include "stage3_data.h"
#include "Back.h"
#include "Player.h"
#include "Shot.h"
#include "Enemy.h"
#include "Effect.h"
#include "UI.h"

#include "Judge.h"

static constexpr int MAX_SCORE = 99999999;

OBJ2DManager* managers[] = {
    &BackManager::getInstance(), 
    &PlayerManager::getInstance(), 
    &OptionManager::getInstance(), 
    &ShotManager::getInstance(), 
    &EnemyManager::getInstance(), 
    &EffectManager::getInstance(), 
    &UIManager::getInstance(), 
};

// �X�e�[�W�f�[�^
StageScript* stageScript[] = {
    stage1Script, // �X�e�[�W1
    stage2Script, // �X�e�[�W2
    stage3Script, // �X�e�[�W3
    nullptr,      // �I���R�[�h
};

void Stage::init()
{
    playerScore = 0;
    state = 0;
    ppScript = stageScript;

    for (auto& manager : managers) { manager->init(); }
}

void Stage::update()
{
    switch (state)
    {
    case 0: // �X�e�[�W�����ݒ�
        pScript = *ppScript;
        timer = 0;
        state++;
        break;

    case 1: // �X�e�[�W�i�s
        timer++;
        while (pScript->time <= timer)
        {   
            if (pScript->data == nullptr) break;
            if (pScript->data != nullptr)
            {
                pScript->data->execute();
            }
            pScript++;
        }

        // �X�e�[�W�N���A�`�F�b�N
        if (pScript->data == nullptr &&
            EnemyManager::getInstance().isAlive() == false)
        {
            ppScript++;
            state = *ppScript ? 0 : 2;
            break;
        }
        break;

    case 2: // �S�X�e�[�W�N���A 
        break;
    }

    for (auto& manager : managers) { manager->update(); }
    judge();
}

void Stage::draw()
{
    for (auto& manager : managers) { manager->draw(); }
    drawScore();

    // STAGE START
    if ((timer < 0x100) && (timer & 0x20))
    {
        std::ostringstream oss;
        oss << "STAGE" << ppScript - stageScript + 1 << " START";
        GameLib::font::textOut(4, oss.str(), { 640, 360 }, { 2, 2 },
            { 0, 1, 1, 1 }, GameLib::TEXT_ALIGN::MIDDLE);
    }
}

void Stage::addScore(int score)
{
    playerScore += score;
    if (playerScore > MAX_SCORE) playerScore = MAX_SCORE;
    if (playerScore > highScore) highScore = playerScore;
}

void Stage::drawScore()
{
    // �X�R�A�\��
    std::ostringstream oss;
    oss << "SCORE " << std::setw(8) << std::setfill('0') << playerScore;
    GameLib::font::textOut(4, oss.str(), { 560, 24 }, { 1, 1 });

    oss.str("");    // �I�u�W�F�N�g�̓��e���N���A
    oss.clear();    // �G���[��Ԃ����Z�b�g
    oss << "HIGH-SCORE " << std::setw(8) << std::setfill('0') << highScore;
    GameLib::font::textOut(4, oss.str(), { 880, 24 }, { 1, 1 });
}

bool Stage::isAllClear()
{
    return !*ppScript;
}

void ScriptEnemy::execute()
{
     EnemyManager::getInstance().searchSet(mover, position);
}

void ScriptBGM::execute()
{
    GameLib::music::stop();
    GameLib::music::play(BGMno, true);
}