#include "Framework.h"
#include "Diablo_Death.h"

Diablo_Death::Diablo_Death()
	: Action(true, L"Textures/Diablo/death.png", 29, 5)
{
}

Diablo_Death::~Diablo_Death()
{
}

void Diablo_Death::Update()
{
	Action::Update();
}

void Diablo_Death::Render()
{
	Action::Render();
}

void Diablo_Death::SetAngleIndex(UINT index)
{
	curAngleIndex = 0;
}
