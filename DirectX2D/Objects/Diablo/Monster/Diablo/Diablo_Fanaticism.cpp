#include "Framework.h"

Diablo_Fanaticism::Diablo_Fanaticism(Transform* transform)
	: Action(L"Textures/Diablo/cast01.png", 18, 8), transform(transform)
{
}

Diablo_Fanaticism::~Diablo_Fanaticism()
{
}

void Diablo_Fanaticism::Update()
{
	Action::Update();
}

void Diablo_Fanaticism::Render()
{
	Action::Render();
}

void Diablo_Fanaticism::Start()
{
	Action::Start();
	Attack();
}

void Diablo_Fanaticism::Attack()
{
	SpellManager::Get()->ActiveSpellNova("DiaNova", transform->GlobalPos());
}
