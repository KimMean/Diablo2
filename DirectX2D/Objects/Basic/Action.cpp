#include "Framework.h"

Action::Action(bool isOneClip, wstring textureFile, int frameX, int frameY)
{
    LoadClip(textureFile, frameX, frameY);
}

Action::Action(wstring textureFile, int frameX, int frameY, bool isLoop, float speed)
{
    LoadClip(textureFile, frameX, frameY, isLoop, speed);
    //vector<Frame*> frames;
    //frames.push_back(new Frame(L"Textures/Sorceress/idle.png", 1, 1, 180, 180));
    //clip = new Clip(frames);
    //clip->Play();
}

Action::~Action()
{
    for (pair<UINT, Clip*> clip : clips)
    {
        delete clip.second;
    }
}

void Action::Update()
{
    clips[curAngleIndex]->Update();
}

void Action::Render()
{
    clips[curAngleIndex]->Render();
    //clip->Render();
}

void Action::Start()
{
    for (pair<UINT, Clip*> clip : clips)
    {
        clip.second->Play();
    }
    //clips[curAngleIndex]->Play();
}

void Action::Stop()
{
    for (pair<UINT, Clip*> clip : clips)
    {
        clip.second->Stop();
    }
}

void Action::End()
{
    if(event != nullptr)
        event();
}

void Action::FrameEvent()
{
    if (frameEvent != nullptr)
        frameEvent();
}

void Action::SetFrameEvent(Event event, int frameNum)
{
    for (pair<UINT, Clip*> clip : clips)
    {
        clip.second->SetEvent(bind(&Action::FrameEvent, this), frameNum);
    }
    frameEvent = event;
}

void Action::SetAngleIndex(UINT index)
{
    curAngleIndex = index;
}

void Action::LoadClip(wstring textureFile, int frameX, int frameY, bool isLoop, float speed)
{
    vector<Frame*> frames;
    Texture* texture = Texture::Add(textureFile);
    Vector2 size = texture->GetSize();
    size.x = size.x / frameX;
    size.y = size.y / frameY;

    for (int y = 0; y < frameY; y++)
    {
        frames.clear();
        for (int x = 0; x < frameX; x++)
        {
            frames.push_back(new Frame(textureFile, size.x * x, size.y * y, (int)size.x, (int)size.y));
        }
        clips[y] = new Clip(frames, isLoop, speed);
        clips[y]->SetEvent(bind(&Action::End, this));
    }
}

void Action::LoadClip(wstring textureFile, int frameX, int frameY)
{
    vector<Frame*> frames;
    Texture* texture = Texture::Add(textureFile);
    Vector2 size = texture->GetSize();
    size.x = size.x / frameX;
    size.y = size.y / frameY;

    for (int y = 0; y < frameY; y++)
    {
        for (int x = 0; x < frameX; x++)
        {
            frames.push_back(new Frame(textureFile, size.x * x, size.y * y, (int)size.x, (int)size.y));
        }
    }
    clips[0] = new Clip(frames, true, 1.0f);
    clips[0]->SetEvent(bind(&Action::End, this));
}

