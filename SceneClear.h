#pragma once
#include "Scene.h"

class SceneClear : public Scene
{
private:
    SceneClear() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    SceneClear(const SceneClear&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    SceneClear& operator=(const SceneClear&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static SceneClear& getInstance()
    {
        static SceneClear instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;
    void deinit() override;
};
