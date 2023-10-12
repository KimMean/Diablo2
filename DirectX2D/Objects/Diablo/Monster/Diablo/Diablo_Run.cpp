#include "Framework.h"

Diablo_Run::Diablo_Run()
	: Action(L"Textures/Diablo/run.png", 22, 8)
{
}

Diablo_Run::~Diablo_Run()
{
}

void Diablo_Run::Update()
{
	Action::Update();
}

void Diablo_Run::Render()
{
	Action::Render();
}
