#pragma once

class RenderManager : public Singleton<RenderManager>
{
private:
    friend class Singleton;

    RenderManager() = default;
    ~RenderManager() = default;

public:
    void Render();

    void AddGameObject(GameObject* object) { objects.push_back(object); }

private:
    vector<GameObject*> objects;
};