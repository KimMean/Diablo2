#include "Framework.h"

Spell_Icon::Spell_Icon(wstring textureFile, wstring downTexture)
	: Button(textureFile)
{
	SetPixelShader(L"SQRT.hlsl");
	SetDownTexture(downTexture);
	Button::SetEvent(bind(&Spell_Icon::LevelUP, this));
}

Spell_Icon::~Spell_Icon()
{
}

void Spell_Icon::Update()
{
	Button::Update();
}

void Spell_Icon::Render()
{
	Button::Render();

	//Float2 pos = { Pos().x + 20, Pos().y - 20 };
	Float2 pos = { GlobalPos().x + 50, GlobalPos().y - 20 };
	Font::Get()->RenderText(to_string(spellLevel), pos);
	//Font::Get()->RenderText(to_string(character->GetLevel()), { 50, WIN_HEIGHT - 80 });
}

void Spell_Icon::LevelUP()
{
	spellLevel++;
	if (spellLevel > 20)
		spellLevel = 20;
}
