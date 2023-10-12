#include "Framework.h"
#include "FireSpellTree.h"

FireSpellTree::FireSpellTree()
	: Panel(L"Textures/UI/Spell/fireSkillTree.png", Vector2(416, 594))
{
	SetPixelShader(L"SQRT.hlsl");
	Pos() += Vector2(0, 15.0f);
	CreateSpells();
}

FireSpellTree::~FireSpellTree()
{
	for (pair<string, Spell_Icon*> icon : spells)
		delete icon.second;
}

void FireSpellTree::Update()
{
	Panel::Update();
	for (pair<string, Spell_Icon*> icon : spells)
		icon.second->Update();
}

void FireSpellTree::Render()
{
	Panel::Render();
	for (pair<string, Spell_Icon*> icon : spells)
		icon.second->Render();
}

void FireSpellTree::CreateSpells()
{
	CreateIcon("FireBolt", { 0, 197 });
	CreateIcon("Warmth", { 123, 197 });
	CreateIcon("Inferno", { -123, 105 });
	CreateIcon("Blaze", { -123, 15 });
	CreateIcon("FireBall", { 0, 15 });
	CreateIcon("FireWall", { -123, -75 });
	CreateIcon("Enchant", { 123, -75 });
	CreateIcon("Meteo", { 0, -167 });
	CreateIcon("FireMastery", { 0, -257 });
	CreateIcon("Hydra", { 123, -257 });
}

void FireSpellTree::CreateIcon(string name, Vector2 pos)
{
	spells[name] = new Spell_Icon(L"Textures/UI/Spell/" + ToWString(name) + L"_Up.png", L"Textures/UI/Spell/" + ToWString(name) + L"_Down.png");
	spells[name]->SetParent(this);
	spells[name]->Pos() = pos;
}
