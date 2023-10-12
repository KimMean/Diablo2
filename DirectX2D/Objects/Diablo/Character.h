#pragma once

class Character : public GameObject
{
public:
	Character();
	~Character();

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

	void SetPath(vector<Vector2> path) { this->path = path; }
	vector<Vector2>& GetPath() { return path; }

	virtual bool IsCollision(Collider* collider, float damage = 0) = 0;

protected :
	void SetAngleIndex(float angle);
	void MovePath();
	//void SetMoveSpeed(float speed) { moveSpeed = speed; }

private :
	void LevelUP();
public:
	void IncressStrength();
	void IncressDexterity();
	void IncressVitality();
	void IncressEnergy();
	void SetMaxHelthPoint(UINT value);
	void SetMaxMagicPoint(UINT value);
	void SetMaxStaminaPoint(UINT value);
	
	virtual void SetCurrentHelthPoint(float incressValue);
	virtual void SetCurrentMagicPoint(float incressValue);
	virtual void SetCurrentStamina(float incressValue);
	virtual void SetExperience(float incressValue);

public :
	string GetNickName() { return nickName; }
	string GetJobName() { return job; }
	UINT GetLevel() { return level; }
	UINT GetMaxExperience() { return maxExperience; }
	UINT GetExperience() { return experience; }
	UINT GetStrength() { return strength; }
	UINT GetDexterity() { return dexterity; }
	UINT GetVitality() { return vitality; }
	UINT GetEnergy() { return energy; }
	UINT GetMaxHelthPoint() { return maxHelthPoint; }
	UINT GetCurHelthPoint() { return curHelthPoint; }
	UINT GetMaxMagicPoint() { return maxMagicPoint; }
	UINT GetCurMagicPoint() { return curMagicPoint; }
	UINT GetMaxStaminaPoint() { return maxStamina; }
	UINT GetCurStaminaPoint() { return curStamina; }
	UINT GetStatusPoint() { return statusPoint; }
	UINT GetSkillPoint() { return skillPoint; }

protected:
	string nickName = "Unknown";
	string job = "Developer";

	UINT level = 1;
	float maxExperience = 100;
	float experience = 0;

	UINT strength = 10;
	UINT dexterity = 10;
	UINT vitality = 10;
	UINT energy = 10;

	float maxHelthPoint = 100;
	float curHelthPoint = 10;
	float maxMagicPoint = 100;
	float curMagicPoint = 10;
	float maxStamina = 100;
	float curStamina = 10;

	UINT statusPoint = 0;
	UINT skillPoint = 0;

	float moveSpeed = 100.0f;

	UINT angleIndex = 0;
	vector<Vector2> path;

	Inventory* inventory;
	Status* status;
	SkillTree* skillTree;
	BasicUI* basicUI;
};