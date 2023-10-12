#include "Framework.h"

BasicUI::BasicUI()
	: Panel(L"Textures/UI/Basic/BasicUI.png", Vector2(465, 81))
{
	Pos() = Vector2(CENTER_X, GetSize().y * 0.5f);

	CreateInformation();
	UpdateWorld();
}

BasicUI::~BasicUI()
{
	delete hpBar;
	delete mpBar;
	delete expBar;
	delete runBtn;
	delete staminaBar;
	delete leftSpell;
	delete rightSpell;
	delete hpPotion;
	delete mpPotion;
}

void BasicUI::Update()
{
	//hpBar->SetAmount(0.3f);
	//mpBar->SetAmount(0.7f);
	//expBar->SetAmount(0.5f);
	//staminaBar->SetAmount(0.7f);
	UpdateInformation();
}

void BasicUI::Render()
{
	Panel::Render();
	hpBar->Render();
	mpBar->Render();
	expBar->Render();
	runBtn->Render();
	staminaBar->Render();
	leftSpell->Render();
	rightSpell->Render();
	hpPotion->Render();
	mpPotion->Render();
}

void BasicUI::SetHelthPointValue(float value)
{
	hpBar->SetAmount(value);
}

void BasicUI::SetMagicPointValue(float value)
{
	mpBar->SetAmount(value);
}

void BasicUI::SetExperienceValue(float value)
{
	expBar->SetAmount(value);
}

void BasicUI::SetStaminaValue(float value)
{
	staminaBar->SetAmount(value);
}

void BasicUI::SetRightSpell(Texture* texture)
{
	rightSpell->SetTexture(texture, true);
}

void BasicUI::UpdateInformation()
{
	runBtn->Update();
	leftSpell->Update();
	rightSpell->Update();
}

void BasicUI::CreateInformation()
{
	hpBar = new Progress(L"Textures/UI/Basic/progressHP.png", true);
	hpBar->SetBackImage(L"Textures/UI/Basic/hpBG.png");
	hpBar->SetResizeTexture(hpBar->GetSize() * 1.5f);
	hpBar->GetBackImage()->SetResizeTexture(hpBar->GetBackImage()->GetSize() * 1.5f);
	hpBar->Pos() = { hpBar->GetBackImage()->GetSize().x * 0.5f , hpBar->GetBackImage()->GetSize().y * 0.5f };
	hpBar->SetParent(this);
	hpBar->UpdateWorld();
	hpBar->GetBackImage()->UpdateWorld();

	mpBar = new Progress(L"Textures/UI/Basic/progressMP.png", true);
	mpBar->SetBackImage(L"Textures/UI/Basic/mpBG.png");
	mpBar->SetResizeTexture(mpBar->GetSize() * 1.5f);
	mpBar->GetBackImage()->SetResizeTexture(mpBar->GetBackImage()->GetSize() * 1.5f);
	mpBar->Pos() = { WIN_WIDTH - mpBar->GetBackImage()->GetSize().x * 0.5f , mpBar->GetBackImage()->GetSize().y * 0.5f };
	mpBar->SetParent(this);
	mpBar->UpdateWorld();
	mpBar->GetBackImage()->UpdateWorld();

	expBar = new Progress(L"Textures/UI/Basic/progressEXP.png");
	expBar->SetResizeTexture(expBar->GetSize() * 1.5f);
	expBar->Pos() = { 355 , 56 };
	expBar->SetParent(this);
	expBar->UpdateWorld();

	//runBtn = new Button(L"Textures/UI/Basic/btn_run_up.png");
	runBtn = new Button(Texture::Add(L"Textures/UI/Basic/btn_run_up.png")->GetSize() * 1.5f);
	runBtn->SetTexture(L"Textures/UI/Basic/btn_run_up.png");
	//runBtn->SetResizeTexture(runBtn->GetSize() * 1.5f);
	runBtn->Pos() = { -205 , -12 };
	runBtn->SetParent(this);
	runBtn->UpdateWorld();

	staminaBar = new Progress(L"Textures/UI/Basic/progressSP.png");
	staminaBar->SetResizeTexture(staminaBar->GetSize() * 1.5f);
	staminaBar->Pos() = { 367 , 28 };
	staminaBar->SetParent(this);
	staminaBar->UpdateWorld();

	leftSpell = new Button(Texture::Add(L"Textures/UI/Spell/SI_basic.png")->GetSize()*1.5f);
	leftSpell-> SetTexture(L"Textures/UI/Spell/SI_basic.png");
	//leftSpell->SetResizeTexture(leftSpell->GetSize() * 1.5f);
	leftSpell->Pos() = { -268 , -5};
	leftSpell->SetParent(this);
	leftSpell->UpdateWorld();

	rightSpell = new Button(Texture::Add(L"Textures/UI/Spell/SI_basic.png")->GetSize() * 1.5f);
	rightSpell->SetTexture(L"Textures/UI/Spell/SI_basic.png");
	//rightSpell->SetResizeTexture(rightSpell->GetSize() * 1.5f);
	rightSpell->Pos() = { 268 , -5};
	rightSpell->SetParent(this);
	rightSpell->UpdateWorld();

	hpPotion = new Quad(Texture::Add(L"Textures/UI/items/hpPotion.png")->GetSize() * 1.5f);
	hpPotion->SetTexture(L"Textures/UI/items/hpPotion.png");
	hpPotion->Pos() = { CENTER_X + 55, 37 };
	hpPotion->SetParent(this);
	hpPotion->UpdateWorld();

	mpPotion = new Quad(Texture::Add(L"Textures/UI/items/mpPotion.png")->GetSize() * 1.5f);
	mpPotion->SetTexture(L"Textures/UI/items/mpPotion.png");
	mpPotion->Pos() = { CENTER_X + 102, 37 };
	mpPotion->SetParent(this);
	mpPotion->UpdateWorld();
}
