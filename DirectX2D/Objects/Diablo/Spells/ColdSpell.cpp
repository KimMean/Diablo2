#include "Framework.h"

ColdSpell::ColdSpell(wstring iconTextureFile)
	: Spell(iconTextureFile)
{
	type = COLD;
}

ColdSpell::~ColdSpell()
{
}

void ColdSpell::Update()
{
	Spell::Update();
}

void ColdSpell::Render()
{
	Spell::Render();
}
