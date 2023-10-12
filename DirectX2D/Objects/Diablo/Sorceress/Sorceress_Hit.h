#pragma once

class Sorceress_Hit : public Action
{
public:
	Sorceress_Hit(Transform* target);
	~Sorceress_Hit();

	void Update();
	void Render();

private:
	Transform* target;

};