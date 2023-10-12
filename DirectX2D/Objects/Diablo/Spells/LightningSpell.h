#pragma once

class LightningSpell : public Spell
{
public:
	LightningSpell(wstring iconTextureFile);
	~LightningSpell();

	virtual void Update() override;
	virtual void Render() override;

private:

};