#pragma once
#include "Obj2d.h"

class EffectManager : public OBJ2DManager
{
private:
    EffectManager() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    EffectManager(const EffectManager&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    EffectManager& operator=(const EffectManager&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static EffectManager& getInstance()
    {
        static EffectManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

private:
    static constexpr int OBJ_MAX = 100;
    OBJ2D objWork[OBJ_MAX];
};

// �v���g�^�C�v�錾
void effectBomb(OBJ2D* obj);
void effectBomb2(OBJ2D* obj);
