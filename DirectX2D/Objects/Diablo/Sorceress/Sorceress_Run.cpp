#include "Framework.h"

Sorceress_Run::Sorceress_Run(Transform* target)
	: Action(L"Textures/Sorceress/run.png", 8, 16), target(target)
{
}

Sorceress_Run::~Sorceress_Run()
{
}

void Sorceress_Run::Update()
{
	Action::Update();
}

void Sorceress_Run::Render()
{
	Action::Render();
}
