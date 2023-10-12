#include "Framework.h"

Diablo_Walk::Diablo_Walk()
	: Action(L"Textures/Diablo/walk.png", 12, 8)
{
}

Diablo_Walk::~Diablo_Walk()
{
}

void Diablo_Walk::Update()
{
	Action::Update();
}

void Diablo_Walk::Render()
{
	Action::Render();
}
