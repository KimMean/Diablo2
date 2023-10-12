#pragma once


class FireSpellTree : public Panel
{
public:
	FireSpellTree();
	~FireSpellTree();

	void Update();
	void Render();

	void CreateSpells();

private:
	void CreateIcon(string name, Vector2 pos);

private:
	unordered_map<string, Spell_Icon*> spells;

};