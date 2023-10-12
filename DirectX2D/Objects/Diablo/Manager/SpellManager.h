#pragma once

class SpellManager : public Singleton<SpellManager>
{
private :
	UINT POOL_SIZE = 200;

private :
	friend class Singleton;
	SpellManager();
	~SpellManager();

public :
	void Update();
	void Render();

	void SetPlayer(Character* target) { player = target; }
	float GetSpellMpPrice(string spellName);
	void ActiveSpell(string spellName, Vector2 pos, Vector2 direction = { 0, 0 });
	void ActiveSpellNova(string spellName, Vector2 pos);
	void CollisionCharacter(Character* character);
	void CollisionMonsters(Monster* monster);

private :
	void CreateSpells();
	template<class T>
	void UpdateSpell(vector<T*> spells);
	template<class T>
	void RenderSpell(vector<T*> spells);
	template<class T>
	void ActiveSpell(vector<T*> spells, Vector2 pos, Vector2 direction = { 0, 0 });
	template<class T>
	void CreateSpell(vector<T*> &vec, T* className);

private:
	unordered_map<string, vector<Spell*>> spells;
	vector<FireBolt*> fireBolt;
	vector<IceBolt*> iceBolt;
	vector<FrozenOrb*> frozenOrb;
	vector<DiaLightning*> diaLightning;
	vector<DiaNova*> diaNova;

	Character* player;
};