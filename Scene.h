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
    virtual void init() {}      // フック
    virtual void deinit() {}    // フック
    virtual void update() {}    // フック
    virtual void draw() {}      // フック

    void setScene(IScene& scene) { pNextScene = &scene; }
    IScene* execute() override;

protected:
    int timer = 0;

private:
    IScene* pNextScene;   // 次のシーン
};

class SceneManager
{
public:
    void execute(IScene& scene);
};
