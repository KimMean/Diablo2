#pragma once

class Action
{
public:
    Action(bool isOneClip, wstring textureFile, int frameX = 1, int frameY = 1);
    Action(wstring textureFile, int frameX = 1, int frameY = 1, bool isLoop = true, float speed = 1.0f);
    ~Action();

    virtual void Update();
    virtual void Render();

    virtual void Start();
    virtual void Stop();
    virtual void End();
    virtual void FrameEvent();

    void SetFrameEvent(Event event, int frameNum);
    void SetEvent(Event event) { this->event = event; }
    virtual void SetAngleIndex(UINT index);

    //Clip* GetClip() { return clip; }

protected:
    void LoadClip(wstring textureFile, int frameX, int frameY, bool isLoop, float speed);
    void LoadClip(wstring textureFile, int frameX, int frameY);

protected:
    map<UINT, Clip*> clips;
    //Clip* clip;

    UINT curAngleIndex = 0;

    Event event = nullptr;
    Event frameEvent = nullptr;
};