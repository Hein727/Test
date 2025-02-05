#pragma once
#include "Obj2d.h"

class ShotManager : public OBJ2DManager
{
private:
    ShotManager() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    ShotManager(const ShotManager&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    ShotManager& operator=(const ShotManager&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static ShotManager& getInstance()
    {
        static ShotManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

private:
    static constexpr int OBJ_MAX = 50;
    OBJ2D objWork[OBJ_MAX];
};

void shotNormal(OBJ2D* obj);
void shotMissile(OBJ2D* obj);
