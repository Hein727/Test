#pragma once
#include "Scene.h"

class SceneGame : public Scene
{
private:
    SceneGame() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    SceneGame(const SceneGame&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    SceneGame& operator=(const SceneGame&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static SceneGame& getInstance()
    {
        static SceneGame instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;

private:
    int state = 0;  // ���
    int frame = 0;
};
