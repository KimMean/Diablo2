#include "Framework.h"

LightningSpell::LightningSpell(wstring iconTextureFile)
	: Spell(iconTextureFile)
{
	type = LIGHTNING;
}

LightningSpell::~LightningSpell()
{
}

void LightningSpell::Update()
{
	Spell::Update();
}

void LightningSpell::Render()
{
	Spell::Render();
}
