#pragma once

class ColdSpell : public Spell
{
public:
	ColdSpell(wstring iconTextureFile);
	~ColdSpell();

	virtual void Update() override;
	virtual void Render() override;

private:

};