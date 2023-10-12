#include "Framework.h"
#include "Sorceress_Hit.h"

Sorceress_Hit::Sorceress_Hit(Transform* target)
	: Action(L"Textures/Sorceress/get_hit.png", 8, 16, false), target(target)
{
}

Sorceress_Hit::~Sorceress_Hit()
{
}

void Sorceress_Hit::Update()
{
	Action::Update();
}

void Sorceress_Hit::Render()
{
	Action::Render();
}
