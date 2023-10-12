#include "Framework.h"

Diablo_Hit::Diablo_Hit()
	: Action(L"Textures/Diablo/hit.png", 6, 8)
{
}

Diablo_Hit::~Diablo_Hit()
{
}

void Diablo_Hit::Update()
{
	Action::Update();
}

void Diablo_Hit::Render()
{
	Action::Render();
}
