#pragma once


class Sorceress_Run : public Action
{
public:
	Sorceress_Run(Transform* target);
	~Sorceress_Run();

	void Update();
	void Render();

private:
	Transform* target;

};