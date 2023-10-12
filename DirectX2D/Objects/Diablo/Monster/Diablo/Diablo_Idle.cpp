#include "Framework.h"

Diablo_Idle::Diablo_Idle()
	: Action(L"Textures/Diablo/idle.png", 12, 8)
{
}

Diablo_Idle::~Diablo_Idle()
{
}

void Diablo_Idle::Update()
{
	Action::Update();
}

void Diablo_Idle::Render()
{
	Action::Render();
}
