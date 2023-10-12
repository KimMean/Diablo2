#include "Framework.h"

FireSpell::FireSpell(wstring iconTextureFile)
	: Spell(iconTextureFile)
{
	type = FIRE;
}

FireSpell::~FireSpell()
{
}

void FireSpell::Update()
{
	Spell::Update();
}

void FireSpell::Render()
{
	Spell::Render();
}
