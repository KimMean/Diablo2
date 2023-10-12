#include "Framework.h"

Panel::Panel(wstring bgTextureFile)
    : Quad(bgTextureFile)
{
    isActive = false;
}

Panel::Panel(wstring bgTextureFile, Vector2 size)
    : Quad(size)
{
    SetTexture(bgTextureFile);
    isActive = false;

}

Panel::~Panel()
{
}

void Panel::Update()
{
    if (!Active()) return;

    UpdateWorld();
}

void Panel::Render()
{
    if (!Active()) return;

    Quad::Render();
}

void Panel::Show()
{
    isActive = true;
}

void Panel::Hide()
{
    isActive = false;
}

