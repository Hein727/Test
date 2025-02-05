#pragma once
#include "Obj2d.h"

class UIManager : public OBJ2DManager
{
public:
    static UIManager& getInstance()
    {
        static UIManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

    void init() override;

private:
    UIManager() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    UIManager(const UIManager&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    UIManager& operator=(const UIManager&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

    static constexpr int OBJ_MAX = 2;
    OBJ2D objWork[OBJ_MAX];
};
