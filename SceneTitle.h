#pragma once
#include "Scene.h"

class SceneTitle : public Scene
{
private:
    SceneTitle() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    SceneTitle(const SceneTitle&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    SceneTitle& operator=(const SceneTitle&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static SceneTitle& getInstance()
    {
        static SceneTitle instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;
    void deinit() override;
};
