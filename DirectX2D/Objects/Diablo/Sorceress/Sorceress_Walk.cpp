#include "Framework.h"

Sorceress_Walk::Sorceress_Walk(Transform* target)
	: Action(L"Textures/Sorceress/walk.png", 8, 16), target(target)
{
}

Sorceress_Walk::~Sorceress_Walk()
{
}

void Sorceress_Walk::Update()
{
	Action::Update();
}

void Sorceress_Walk::Render()
{
	Action::Render();
}
