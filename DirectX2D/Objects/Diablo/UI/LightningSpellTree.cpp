#include "Framework.h"

LightningSpellTree::LightningSpellTree()
	: Panel(L"Textures/UI/Spell/lightningSkillTree.png", Vector2(416, 594))
{
	SetPixelShader(L"SQRT.hlsl");
	Pos() += Vector2(0, 15.0f);
	CreateSpells();
}

LightningSpellTree::~LightningSpellTree()
{
	for (pair<string, Spell_Icon*> icon : spells)
		delete icon.second;
}

void LightningSpellTree::Update()
{
	Panel::Update();
	for (pair<string, Spell_Icon*> icon : spells)
		icon.second->Update();
}

void LightningSpellTree::Render()
{
	Panel::Render();
	for (pair<string, Spell_Icon*> icon : spells)
		icon.second->Render();
}

void LightningSpellTree::CreateSpells()
{
	CreateIcon("ChargedBolt", { 0, 197 });
	CreateIcon("ElectroField", { -123, 105 });
	CreateIcon("Telekinesis", { 123, 105 });
	CreateIcon("Nova", { -123, 15 });
	CreateIcon("Lightning", { 0, 15 });
	CreateIcon("ChainLightning", { 0, -75 });
	CreateIcon("Teleport", { 123, -75 });
	CreateIcon("ThonderStom", { -123, -167 });
	CreateIcon("EnergyShild", { 123, -167 });
	CreateIcon("LightningMastery", { 0, -257 });
}

void LightningSpellTree::CreateIcon(string name, Vector2 pos)
{
	spells[name] = new Spell_Icon(L"Textures/UI/Spell/" + ToWString(name) + L"_Up.png", L"Textures/UI/Spell/" + ToWString(name) + L"_Down.png");
	spells[name]->SetParent(this);
	spells[name]->Pos() = pos;
}
