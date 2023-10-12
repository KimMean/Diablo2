#pragma once

class DiaLightning : public Spell
{
public:
	DiaLightning();
	~DiaLightning();

	void Update() override;
	void Render() override;

	void Fire(Vector2 pos, Vector2 direction = { 0, 0 });

	CircleCollider* GetCollider() { return collider; }

private:
	Action* action;
	CircleCollider* collider;

	Vector2 direction;
	float speed = 300.0f;
	float duration = 5.0f;
	float curTime = 0.0f;

};