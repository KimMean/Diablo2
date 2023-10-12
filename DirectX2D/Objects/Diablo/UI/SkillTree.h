#pragma once

class SkillTree : public Panel
{
public:
	SkillTree();
	~SkillTree();

	void Update();
	void Render();

	void ClickColdBtn() { ChangeTargetPanel(coldSpell); }
	void ClickLightningBtn() { ChangeTargetPanel(lightningSpell); }
	void ClickFireBtn() { ChangeTargetPanel(fireSpell); }

	Collider* GetCollider() { return collider; }

private:
	void CreateSpellTree();
	void CreateSpellBtn(Button*& btn, Vector2 pos);
	void ChangeTargetPanel(Panel* panel);


private :
	RectCollider* collider;

	Panel* targetPanel = nullptr;

	Button* coldBtn;
	Button* lightningBtn;
	Button* fireBtn;

	ColdSpellTree* coldSpell;
	LightningSpellTree* lightningSpell;
	FireSpellTree* fireSpell;


};