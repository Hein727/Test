#pragma once
#include "Obj2d.h"

class BackManager : public OBJ2DManager
{
private:
    BackManager() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    BackManager(const BackManager&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    BackManager& operator=(const BackManager&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static BackManager& getInstance()
    {
        static BackManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

    void init() override;

private:
    static constexpr int OBJ_MAX = 2;
    OBJ2D objWork[OBJ_MAX];
};

void backUpdate(OBJ2D* obj);
