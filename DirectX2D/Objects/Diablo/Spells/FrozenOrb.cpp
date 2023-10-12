#include "Framework.h"

FrozenOrb::FrozenOrb()
	: ColdSpell(L"Textures/UI/Spell/FrozenOrb_Up.png")
{
	action = new Action(L"Textures/Spell/IceOrb.png", 16, 1, true);

	action->Start();
	duration = 2.0f;
}

FrozenOrb::~FrozenOrb()
{
	delete action;
}

void FrozenOrb::Update()
{
	boltDelay += DELTA;
	if (boltDelay > 0.2f)
	{
		float x = cos(ANGLE * boltCount);
		float y = sin(ANGLE * boltCount);

		Vector2 dir = { x, y };
		dir.Normalize();
		SpellManager::Get()->ActiveSpell("IceBolt", GlobalPos(), dir);
		dir.x = dir.x * -1;
		dir.y = dir.y * -1;
		SpellManager::Get()->ActiveSpell("IceBolt", GlobalPos(), dir);
		boltDelay -= 0.2f;
		boltCount++;
	}

	action->Update();
	//float tempSpeed = speed * (1.0f - direction.y * 0.5f);
	Pos() += direction * speed * DELTA;
	UpdateWorld();
	ColdSpell::Update();
}

void FrozenOrb::Render()
{
	SetRender();
	Environment::Get()->SetAdditiveBlend();
	action->Render();
	Environment::Get()->SetAlphaBlend();
	ColdSpell::Render();
}

void FrozenOrb::Fire(Vector2 pos, Vector2 direction)
{
	Pos() = pos;
	UpdateWorld();

	direction.Normalize();
	this->direction = direction;
	curTime = 0;
	boltCount = 0;

	action->Start();
	action->SetAngleIndex(0);


	isActive = true;
}
