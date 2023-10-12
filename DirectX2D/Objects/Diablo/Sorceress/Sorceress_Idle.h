#pragma once

class Sorceress_Idle : public Action
{
public:
	Sorceress_Idle(Transform* target);
	~Sorceress_Idle();

	void Update();
	void Render();

private:
	Transform* target;

};