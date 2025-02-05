#pragma once
#include "Obj2d.h"

class PlayerManager : public OBJ2DManager
{
private:
    PlayerManager() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    PlayerManager(const PlayerManager&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    PlayerManager& operator=(const PlayerManager&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    enum IWorkIndex
    {
        PAD_STATE,
        PAD_TRG,
    };

    static PlayerManager& getInstance()
    {
        static PlayerManager instance;
        return instance;
    }

    OBJ2D* begin() override { return &objWork[0]; }
    OBJ2D* end() override { return &objWork[OBJ_MAX]; }

    void init() override;
    void update() override;
    bool isAlive();

private:
    static constexpr int OBJ_MAX = 1;
    OBJ2D objWork[OBJ_MAX];
};

void playerMove(OBJ2D* obj);
void playerUpdate(OBJ2D* obj);

//----------------------------------------------------------------

class OptionManager : public OBJ2DManager
{
private:
    OptionManager() = default;
    OptionManager(const OptionManager&) = delete;
    OptionManager& operator=(const OptionManager&) = delete;

public:
    static OptionManager& getInstance()
    {
        static OptionManager instance;
        return instance;
    }

    OBJ2D* begin() { return &objWork[0]; }
    OBJ2D* end() { return &objWork[OBJ_MAX]; }

    static constexpr int OBJ_MAX = 4;

private:
    OBJ2D objWork[OBJ_MAX];
};

void optionNormal(OBJ2D* obj);
