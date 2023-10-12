#pragma once


class FrozenOrb : public ColdSpell
{
private :
	float ANGLE = XM_2PI / 7;

public:
	FrozenOrb();
	~FrozenOrb();

	void Update() override;
	void Render() override;

	void Fire(Vector2 pos, Vector2 direction = { 0, 0 });

private:
	Action* action;

	Vector2 direction;
	float speed = 150.0f;

	float boltDelay = 0.0f;
	int boltCount = 0;
};