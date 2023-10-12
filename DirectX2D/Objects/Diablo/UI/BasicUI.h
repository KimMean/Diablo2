#pragma once

class BasicUI : public Panel
{
public:
	BasicUI();
	~BasicUI();

	void Update();
	void Render();


	void SetHelthPointValue(float value);
	void SetMagicPointValue(float value);
	void SetExperienceValue(float value);
	void SetStaminaValue(float value);

	void SetRightSpell(Texture* texture);
private:
	void UpdateInformation();
	void CreateInformation();

private :
	Progress* hpBar;
	Progress* mpBar;

	Progress* expBar;
	Button* runBtn;
	Progress* staminaBar;

	Button* leftSpell;
	Button* rightSpell;

	Quad* hpPotion;
	Quad* mpPotion;



	// hp b, f
	// mp b, f
	// skill 1, 2
	// status
	// skill
	// exp
	// stamina
	// belt
	
};