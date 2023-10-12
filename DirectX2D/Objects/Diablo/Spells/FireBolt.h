#pragma once

class FireBolt : public FireSpell
{
public:
	FireBolt();
	~FireBolt();

	void Update() override;
	void Render() override;

	void Fire(Vector2 pos, Vector2 direction = { 0, 0 });

	CircleCollider* GetCollider() { return collider; }

private:
	Action* action;
	CircleCollider* collider;

	Vector2 direction;
	float speed = 300.0f;
};