#include "Framework.h"

Button::Button(wstring textureFile)
    : Quad(textureFile)
{
    defaultTexture = Texture::Add(textureFile);
    collider = new RectCollider(size);
    collider->SetParent(this);
}

Button::Button(Vector2 size)
    : Quad(size)
{
    collider = new RectCollider(size);
    collider->SetParent(this);
}

Button::~Button()
{
    delete collider;
}

void Button::Update()
{
    if (!isActive) return;

    if (collider->IsPointCollision(mousePos))
    {
        if (KEY_DOWN(VK_LBUTTON))
            isDownCheck = true;

        if (KEY_PRESS(VK_LBUTTON))
            state = DOWN;
        else
            state = OVER;

        if (isDownCheck && KEY_UP(VK_LBUTTON))
        {
            state = NONE;

            if (event != nullptr)
            {
                Audio::Get()->Play("Button");
                event();
            }

            if (paramEvent != nullptr)
                paramEvent(object);

            isDownCheck = false;
        }
    }
    else
    {
        state = NONE;

        if (KEY_UP(VK_LBUTTON))
            isDownCheck = false;
    }

    switch (state)
    {
    case Button::NONE:
        colorBuffer->Get() = NONE_COLOR;
        Quad::SetTexture(defaultTexture);
        break;
    case Button::DOWN:
        //colorBuffer->Get() = DOWN_COLOR;
        if(downTexture)
            Quad::SetTexture(downTexture);
        break;
    case Button::OVER:
        //colorBuffer->Get() = OVER_COLOR;
        if (overTexture)
            Quad::SetTexture(overTexture);
        break;    
    }

    UpdateWorld();
    collider->UpdateWorld();
}

void Button::Render()
{
    if (!isActive) return;

    Quad::Render();
    collider->Render();
}

void Button::SetTexture(Texture* texture, bool needSqrt)
{
    if(needSqrt)
        SetPixelShader(L"SQRT.hlsl");
    else
        SetPixelShader(L"UV.hlsl");

    Quad::SetTexture(texture);
    defaultTexture = GetTexture();
}

void Button::SetTexture(wstring textureFile)
{
    Quad::SetTexture(textureFile);
    defaultTexture = GetTexture();
}
