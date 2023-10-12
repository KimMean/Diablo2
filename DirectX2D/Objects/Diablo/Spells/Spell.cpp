#include "Framework.h"

Spell::Spell()
{
	isActive = false;
}

Spell::Spell(wstring iconTextureFile)
{
	icon = Texture::Add(iconTextureFile);
	isActive = false;
}

Spell::~Spell()
{
}

void Spell::Update()
{

	curTime += DELTA;
	if (curTime > duration)
	{
		curTime -= duration;
		isActive = false;
	}
}

void Spell::Render()
{
}
