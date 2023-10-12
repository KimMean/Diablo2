#pragma once

class Sorceress_Walk : public Action
{
public:
	Sorceress_Walk(Transform* target);
	~Sorceress_Walk();

	void Update();
	void Render();

private:
	Transform* target;

};