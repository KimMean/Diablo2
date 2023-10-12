#pragma once

class Spell : public GameObject
{
public :
	enum PropertyType
	{
		NONE,
		COLD,
		LIGHTNING,
		FIRE
	};
public:
	Spell();
	Spell(wstring iconTextureFile);
	~Spell();

	virtual void Update();
	virtual void Render();

	UINT GetSpellLevel() { return spellLevel; }
	Texture* GetIcon() { return icon; }
	float GetSpellDamage() { return damage; }
	float GetMpPrice() { return mpPrice; }

protected:
	string spellName;
	PropertyType type = NONE;
	UINT spellLevel;

	Texture* icon;
	float damage = 10.0f;
	float mpPrice = 10.0f;

	float duration = 3.0f;
	float curTime = 0.0f;


};