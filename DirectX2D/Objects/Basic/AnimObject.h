#pragma once

class AnimObject : public GameObject
{
public:
    AnimObject();
    ~AnimObject();

    void Update();
    void Render();

    void AddClip(int key, Clip* clip) { clips[key] = clip; }

    void SetClip(int key);

protected:
    ColorBuffer* colorBuffer;

    map<int, Clip*> clips;
    Clip* curClip = nullptr;
};