#include "Framework.h"

ColdSpellTree::ColdSpellTree()
	: Panel(L"Textures/UI/Spell/coldSkillTree.png", Vector2(416, 594))
{
	SetPixelShader(L"SQRT.hlsl");
	Pos() += Vector2(0, 15.0f);

	CreateSpells();
}

ColdSpellTree::~ColdSpellTree()
{
	for (pair<string, Spell_Icon*> icon : spells)
		delete icon.second;
}

void ColdSpellTree::Update()
{
	Panel::Update();

	for (pair<string, Spell_Icon*> icon : spells)
		icon.second->Update();
}

void ColdSpellTree::Render()
{
	Panel::Render();
	for (pair<string, Spell_Icon*> icon : spells)
		icon.second->Render();
}

void ColdSpellTree::CreateSpells()
{
	CreateIcon("IceBolt", { 0, 197 });
	CreateIcon("FrozenArmor", { 123, 197 });
	CreateIcon("FrostNova", { -123, 105 });
	CreateIcon("IceBlast", { 0, 105 });
	CreateIcon("ShiverArmor", { 123, 15 });
	CreateIcon("GlacierSpike", { 0, -75 });
	CreateIcon("Blizard", { -123, -167 });
	CreateIcon("ChillingArmor", { 123, -167 });
	CreateIcon("FrozenOrb", { -123, -257 });
	CreateIcon("ColdMastery", { 0, -257 });
}

void ColdSpellTree::CreateIcon(string name, Vector2 pos)
{
	spells[name] = new Spell_Icon(L"Textures/UI/Spell/" + ToWString(name) + L"_Up.png", L"Textures/UI/Spell/" + ToWString(name) + L"_Down.png");
	spells[name]->SetParent(this);
	spells[name]->Pos() = pos;
}
