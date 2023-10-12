#pragma once

class Diablo_Lightning : public Action
{
public:
	Diablo_Lightning(Transform* transform);
	~Diablo_Lightning();

	void Update();
	void Render();
	void Start();

	void SetTarget(Transform* target) { this->target = target; }

private:
	Transform* transform;
	Transform* target;
	float delay = 0.0f;
};