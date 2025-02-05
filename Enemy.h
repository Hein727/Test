#pragma once
#include "Obj2d.h"

class EnemyManager : public OBJ2DManager
{
private:
    EnemyManager() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    EnemyManager(const EnemyManager&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    EnemyManager& operator=(const EnemyManager&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static EnemyManager& getInstance()
    {
        static EnemyManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }
    void update() override;
    bool isAlive();

private:
    static constexpr int OBJ_MAX = 100;
    OBJ2D objWork[OBJ_MAX];
};

// �v���g�^�C�v�錾
void enemyShot(OBJ2D* obj);			// �G�̒e
void enemySin(OBJ2D* obj);			// �T�C���J�[�u
void enemyFall(OBJ2D* obj);			// ������
void enemyCannon(OBJ2D* obj);       // �C��
void enemyHoming(OBJ2D* obj);       // �z�[�~���O
void enemyAppear(OBJ2D* obj);       // �ˑR�o������G
