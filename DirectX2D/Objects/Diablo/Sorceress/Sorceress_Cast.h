#pragma once

class Sorceress_Cast : public Action
{
public:
	Sorceress_Cast(Transform* target);
	~Sorceress_Cast();

	void Update();
	void Render();
	void Start() override;

	void SetCastType(string type) { this->castType = type; }
	void Cast();

private:
	Transform* target;
	map<string, Action*> castAction;
	string castType;
};