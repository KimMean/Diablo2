#pragma once

class Sorceress : public Character
{
private :
	enum ActionType
	{
		IDLE,
		WALK,
		RUN,
		CAST,
		HIT
	};

public:
	Sorceress();
	~Sorceress();

	void Update();
	void Render();
	void PostRender();

	void SetSpell(string spellName, bool isLeftSpell = false);
	void ActiveSpell();

	bool IsCollision(Collider* collider, float damage = 0) override;

	void SetCurrentHelthPoint(float incressValue) override;
	void SetCurrentMagicPoint(float incressValue) override;
	void SetCurrentStamina(float incressValue) override;
	void SetExperience(float incressValue) override;

private :
	void Control();
	void Move();
	void Attack();
	void SelectSpell();

	void CreateActions();
	void SetIdle();
	void SetAction(int type);

	void CreateSpells();

private:
	map<ActionType, Action*> actions;
	ActionType curAction = IDLE;

	RectCollider* collider;

	unordered_map<string, Spell*> spells;
	Spell* leftSpell = nullptr;
	Spell* rightSpell = nullptr;

	string spellName;
	Vector2 direction;

	//IceBolt* bolt;

	//Quad* test;



};