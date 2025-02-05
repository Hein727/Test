#pragma once
#include "Scene.h"

class SceneOver : public Scene
{
private:
    SceneOver() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    SceneOver(const SceneOver&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    SceneOver& operator=(const SceneOver&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static SceneOver& getInstance()
    {
        static SceneOver instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;
    void deinit() override;
};
