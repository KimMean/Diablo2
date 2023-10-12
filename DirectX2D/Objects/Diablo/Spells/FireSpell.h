#pragma once

class FireSpell : public Spell
{
public:
	FireSpell(wstring iconTextureFile);
	~FireSpell();

	virtual void Update() override;
	virtual void Render() override;

private:

};