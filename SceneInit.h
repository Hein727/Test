#pragma once
#include "Scene.h"

class SceneInit : public IScene
{
private:
    SceneInit() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    SceneInit(const SceneInit&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    SceneInit& operator=(const SceneInit&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static SceneInit& getInstance()
    {
        static SceneInit instance;
        return instance;
    }
    IScene* execute() override;
};

class SceneDeinit : public IScene
{
private:
    SceneDeinit() = default;  // �f�t�H���g�R���X�g���N�^�Bprivate �ɂ��āA�O������̃C���X�^���X����h���B
    SceneDeinit(const SceneDeinit&) = delete;  // �R�s�[�R���X�g���N�^���폜�B�C���X�^���X�̃R�s�[��h���B
    SceneDeinit& operator=(const SceneDeinit&) = delete;  // ������Z�q���폜�B�C���X�^���X�̑����h���B

public:
    static SceneDeinit& getInstance()
    {
        static SceneDeinit instance;
        return instance;
    }
    IScene* execute() override;
};
