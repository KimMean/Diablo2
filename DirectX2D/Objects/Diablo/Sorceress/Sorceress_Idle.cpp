#include "Framework.h"


Sorceress_Idle::Sorceress_Idle(Transform* target)
	: Action(L"Textures/Sorceress/idle.png", 8, 16), target(target)
{
}

Sorceress_Idle::~Sorceress_Idle()
{
}

void Sorceress_Idle::Update()
{
	Action::Update();
}

void Sorceress_Idle::Render()
{
	Action::Render();
}
