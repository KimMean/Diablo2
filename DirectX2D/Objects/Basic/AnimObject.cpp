#include "Framework.h"

AnimObject::AnimObject()
{
    colorBuffer = new ColorBuffer();
}

AnimObject::~AnimObject()
{
    for (pair<int, Clip*> clip : clips)
        delete clip.second;

    delete colorBuffer;
}

void AnimObject::Update()
{
    if (curClip == nullptr) return;

    curClip->Update();
    UpdateWorld();
}

void AnimObject::Render()
{
    if (curClip == nullptr) return;

    if (!CAM->ContainFrustum(GlobalPos(), curClip->GetCurFrame()->GetSize()))
        return;

    colorBuffer->SetPS(0);
    GameObject::SetRender();

    curClip->Render();
}

void AnimObject::SetClip(int key)
{
    if (curClip != clips[key])
    {
        curClip = clips[key];
        curClip->Play();
    }
}
