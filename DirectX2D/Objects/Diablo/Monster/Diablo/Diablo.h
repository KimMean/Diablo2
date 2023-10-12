#pragma once

class Diablo : public Monster
{
private :
	enum ActionType
	{
		IDLE,
		WALK,
		RUN,
		ATTACK,
		HIT,
		DEAD,
		LIGHTNING,
		FANATICISM
	};

public:
	Diablo();
	~Diablo();

	void Update() override;
	void Render() override;
	void PostRender();

	void SetCurrentHelthPoint(float incressValue) override;

	void SetTarget(Transform* target);
	bool IsCollision(Collider* collider, float damage = 0);
	bool IsCollision(Vector2 pos);

private :
	void Control();
	void Move();
	void Attack();
	void Death();

	void Patrol();
	void Trace();
	void DetectionTarget();

	void SetIdle();
	void SetAction(int type);

	void InitDiablo();
	void CreateActions();

	void SetState(State state);

private:
	map<ActionType, Action*> actions;
	ActionType curAction = IDLE;
	RectCollider* hitBox;
	
	float attackDelay = 0.0f;


	float walkSpeed = 100.0f;
	float runSpeed = 200.0f;

};