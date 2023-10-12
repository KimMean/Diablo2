#pragma once

class Status : public Panel
{
public:
	Status();
	~Status();

	void Update();
	void Render();

	void SetCharacter(class Character* character);
	void Hide();
	Collider* GetCollider() { return collider; }

private :
	void UpdateInformation();
	void CreateStatusButton();

private:
	RectCollider* collider;

	Character* character = nullptr;

	Button* cancelBtn;

	unordered_map<string, Button*> statusPointBtn;

};