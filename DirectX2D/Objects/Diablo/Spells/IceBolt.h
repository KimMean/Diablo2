#pragma once

class IceBolt : public ColdSpell
{
public:
	IceBolt();
	~IceBolt();

	void Update() override;
	void Render() override;

	void Fire(Vector2 pos, Vector2 direction = { 0, 0 });

	CircleCollider* GetCollider() { return collider; }

private:
	Action* action;
	CircleCollider* collider;

	Vector2 direction;
	float speed = 200.0f;
};