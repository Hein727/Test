#pragma once

inline constexpr int SCREEN_WIDTH = 1280;
inline constexpr int SCREEN_HEIGHT = 720;

class IScene
{
public:
    virtual IScene* execute() = 0;
};

class Scene : public IScene
{
public:
    virtual void init() {}      // �t�b�N
    virtual void deinit() {}    // �t�b�N
    virtual void update() {}    // �t�b�N
    virtual void draw() {}      // �t�b�N

    void setScene(IScene& scene) { pNextScene = &scene; }
    IScene* execute() override;

protected:
    int timer = 0;

private:
    IScene* pNextScene;   // ���̃V�[��
};

class SceneManager
{
public:
    void execute(IScene& scene);
};
