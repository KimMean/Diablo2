#pragma once

class Monster : public GameObject
{
protected :
	const float PATROL_TIME = 2.0f;
	const float PATROL_RANGE = 150.0f;
	const float TRACE_TIME = 1.0f;
	const float TRACE_RANGE = 250.0f;

protected :
	enum State
	{
		PATROL, TRACE, ATTACK,
		HIT, DEAD
	};

public:
	Monster();
	~Monster();

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

	virtual void SetTarget(Transform* target) { this->target = target; }
	void SetPath(vector<Vector2> path) { this->path = path; }
	vector<Vector2>& GetPath() { return path; }
	
	virtual bool IsCollision(Collider* collider, float damage = 0) = 0;

public :
	virtual void SetCurrentHelthPoint(float incressValue);
	float GetExperience() { return experience; }
	bool GetIsDead() { return isDead; }

protected :
	void Patrol();
	void Trace();
	bool IsCollisionTarget();
	void MovePath();
	void UpdatePath(Vector2 pos, Vector2 targetPos);
	void UpdatePath(Vector2 pos, float range);
	void SetAngleIndex(float angle);
	void InitMonster();

protected :
	string name = "Monster";
	State curState = PATROL;
	Progress* hpBar;

	CircleCollider* traceCollider;

	Transform* target = nullptr;
	
	bool isDead = false;
	bool isPatrol = false;
	float waitingTime = 0.0f;

	float attackPower;
	float maxHelthPoint;
	float curHelthPoint;

	float experience = 20.0f;
	float defaultSpeed = 100.0f;
	float speed = 100.0f;

	UINT angleIndex = 0;
	vector<Vector2> path;
};