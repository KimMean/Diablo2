#include "Framework.h"

Diablo_Attack::Diablo_Attack()
	: Action(L"Textures/Diablo/atk01.png", 20, 8)
{
}

Diablo_Attack::~Diablo_Attack()
{
}

void Diablo_Attack::Update()
{
	Action::Update();
}

void Diablo_Attack::Render()
{
	Action::Render();
}
