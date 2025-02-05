#pragma once
#include "Scene.h"

class SceneDemo : public Scene
{
private:
    SceneDemo() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    SceneDemo(const SceneDemo&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    SceneDemo& operator=(const SceneDemo&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static SceneDemo& getInstance()
    {
        static SceneDemo instance;
        return instance;
    }

    void init() override;
    void update() override;
    void draw() override;
};
