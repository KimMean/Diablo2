#include "Framework.h"

Diablo_Lightning::Diablo_Lightning(Transform* transform)
	: Action(L"Textures/Diablo/cast02.png", 17, 8), transform(transform)
{
}

Diablo_Lightning::~Diablo_Lightning()
{
}

void Diablo_Lightning::Update()
{
	Action::Update();
	delay += DELTA;
	if (delay > 0.2f)
	{
		delay -= 0.2f;

		Vector2 direction = target->GlobalPos() - transform->GlobalPos();
		direction.Normalize();
		SpellManager::Get()->ActiveSpell("DiaLightning", transform->GlobalPos(), direction);
	}

}

void Diablo_Lightning::Render()
{
	Action::Render();
}

void Diablo_Lightning::Start()
{
	Action::Start();
	Audio::Get()->Play("Diablo_Lightning");
}
