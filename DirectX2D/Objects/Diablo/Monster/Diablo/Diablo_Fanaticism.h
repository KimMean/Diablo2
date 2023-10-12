#pragma once

class Diablo_Fanaticism : public Action
{
public:
	Diablo_Fanaticism(Transform* transform);
	~Diablo_Fanaticism();

	void Update();
	void Render();

	void Start() override;

	void SetTarget(Transform* target) { this->target = target; }

	void Attack();

private:
	Transform* transform;
	Transform* target;

};