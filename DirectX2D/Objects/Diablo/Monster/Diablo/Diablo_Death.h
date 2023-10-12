#pragma once

class Diablo_Death : public Action
{
public:
	Diablo_Death();
	~Diablo_Death();

	void Update();
	void Render();

	void SetAngleIndex(UINT index) override;

private:

};