#pragma once

class Spell_Icon : public Button
{
public:
	Spell_Icon(wstring textureFile, wstring downTexture);
	~Spell_Icon();

	void Update();
	void Render();

	void LevelUP();

private:
	UINT spellLevel = 0;
};