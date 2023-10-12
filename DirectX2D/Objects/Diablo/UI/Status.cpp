#include "Framework.h"

Status::Status()
	: Panel(L"Textures/UI/Status/Status.png", Vector2(480, 640))
{
	Pos() = Vector2(GetSize().x * 0.5f, WIN_HEIGHT - GetSize().y * 0.5f);
	
	collider = new RectCollider(Vector2(480, 640));
	collider->SetParent(this);

	cancelBtn = new Button(Vector2(45, 45));
	cancelBtn->SetTexture(L"Textures/UI/btn_cancel_up.png");
	cancelBtn->SetDownTexture(L"Textures/UI/btn_cancel_down.png");
	cancelBtn->Pos() = { -25, -280 };
	cancelBtn->SetParent(this);
	cancelBtn->SetEvent(bind(&Status::Hide, this));

	//CreateStatusButton();

	UpdateWorld();
	collider->UpdateWorld();

}

Status::~Status()
{
	for (pair<string, Button*> btn : statusPointBtn)
		delete btn.second;
}

void Status::Update()
{
	if (!Active()) return;

	cancelBtn->Update();
	for (pair<string, Button*> btn : statusPointBtn)
	{
		btn.second->Update();
	}
}

void Status::Render()
{
	if (!Active()) return;
	Panel::Render();
	for (pair<string, Button*> btn : statusPointBtn)
	{
		btn.second->Render();
	}
	cancelBtn->Render();
	collider->Render();

	UpdateInformation();
}

void Status::Hide()
{
	isActive = false;
}

void Status::SetCharacter(Character* character)
{
	this->character = character;
	CreateStatusButton();
	for (pair<string, Button*> btn : statusPointBtn)
	{
		btn.second->SetParent(this);
		btn.second->UpdateWorld();
	}
}

void Status::UpdateInformation()
{
	if (!character) return;

	//string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	Font::Get()->RenderText(character->GetNickName(), {140, WIN_HEIGHT - 20});
	Font::Get()->RenderText(character->GetJobName(), {380, WIN_HEIGHT - 20});
	Font::Get()->RenderText("레벨", {50, WIN_HEIGHT - 60});
	Font::Get()->RenderText(to_string(character->GetLevel()), {50, WIN_HEIGHT - 80});

	Font::Get()->RenderText("경험치", { 180, WIN_HEIGHT - 60 });
	Font::Get()->RenderText(to_string(character->GetExperience()), { 180, WIN_HEIGHT - 80 });

	Font::Get()->RenderText("다음레벨", { 380, WIN_HEIGHT - 60 });
	Font::Get()->RenderText(to_string(character->GetMaxExperience()), { 380, WIN_HEIGHT - 80 });

	Font::Get()->RenderText("힘", { 65, WIN_HEIGHT - 135 });
	Font::Get()->RenderText(to_string(character->GetStrength()), { 145, WIN_HEIGHT - 135 });
	Font::Get()->RenderText("스킬이름", { 310, WIN_HEIGHT - 135 });
	Font::Get()->RenderText(to_string(character->GetStrength() * 3), { 430, WIN_HEIGHT - 135 });
	Font::Get()->RenderText("스킬이름", { 310, WIN_HEIGHT - 170 });
	Font::Get()->RenderText(to_string(character->GetStrength() * 13), { 430, WIN_HEIGHT - 170 });

	Font::Get()->RenderText("민첩성", { 65, WIN_HEIGHT - 225 });
	Font::Get()->RenderText(to_string(character->GetDexterity()), { 145, WIN_HEIGHT - 225 });
	Font::Get()->RenderText("공격등급", { 310, WIN_HEIGHT - 225 });
	Font::Get()->RenderText(to_string(character->GetDexterity() * 3), { 435, WIN_HEIGHT - 225 });
	Font::Get()->RenderText("공격등급", { 310, WIN_HEIGHT - 260 });
	Font::Get()->RenderText(to_string(character->GetDexterity() * 23), { 435, WIN_HEIGHT - 260 });
	Font::Get()->RenderText("방어", { 310, WIN_HEIGHT - 300 });
	Font::Get()->RenderText(to_string(character->GetDexterity() * 4), { 435, WIN_HEIGHT - 300 });

	Font::Get()->RenderText("생명력", { 65, WIN_HEIGHT - 353 });
	Font::Get()->RenderText(to_string(character->GetVitality()), { 145, WIN_HEIGHT - 353 });
	Font::Get()->RenderText("스테미너", { 290, WIN_HEIGHT - 353 });
	Font::Get()->RenderText(to_string(character->GetCurStaminaPoint()), { 375, WIN_HEIGHT - 353 });
	Font::Get()->RenderText(to_string(character->GetMaxStaminaPoint()), { 435, WIN_HEIGHT - 353 });
	Font::Get()->RenderText("라이프", { 290, WIN_HEIGHT - 389 });
	Font::Get()->RenderText(to_string(character->GetCurHelthPoint()), { 375, WIN_HEIGHT - 389 });
	Font::Get()->RenderText(to_string(character->GetMaxHelthPoint()), { 435, WIN_HEIGHT - 389 });

	Font::Get()->RenderText("에너지", { 65, WIN_HEIGHT - 445 });
	Font::Get()->RenderText(to_string(character->GetEnergy()), { 145, WIN_HEIGHT - 445 });
	Font::Get()->RenderText("마나", { 290, WIN_HEIGHT - 445 });
	Font::Get()->RenderText(to_string(character->GetCurMagicPoint()), { 375, WIN_HEIGHT - 445 });
	Font::Get()->RenderText(to_string(character->GetMaxMagicPoint()), { 435, WIN_HEIGHT - 445 });


	Font::Get()->RenderText("파이어 저항력", { 330, WIN_HEIGHT - 505 });
	Font::Get()->RenderText(to_string(character->GetDexterity() + 5), { 435, WIN_HEIGHT - 505 });
	Font::Get()->RenderText("콜드 저항력", { 330, WIN_HEIGHT - 540 });
	Font::Get()->RenderText(to_string(character->GetDexterity() + 10), { 435, WIN_HEIGHT - 540 });
	Font::Get()->RenderText("라이트닝 저항력", { 330, WIN_HEIGHT - 575 });
	Font::Get()->RenderText(to_string(character->GetDexterity() + 5), { 435, WIN_HEIGHT - 575 });
	Font::Get()->RenderText("포이즌 저항력", { 330, WIN_HEIGHT - 610 });
	Font::Get()->RenderText(to_string(character->GetDexterity() - 5), { 435, WIN_HEIGHT - 610 });


	Font::Get()->RenderText("Point", { 210, WIN_HEIGHT - 530 });
	Font::Get()->RenderText(to_string(character->GetStatusPoint()), { 210, WIN_HEIGHT - 550 });

}

void Status::CreateStatusButton()
{
	statusPointBtn["STR"] = new Button(Vector2(40, 40));
	statusPointBtn["STR"]->SetTexture(L"Textures/UI/btn_levelup_up.png");
	statusPointBtn["STR"]->SetDownTexture(L"Textures/UI/btn_levelup_down.png");
	statusPointBtn["STR"]->Pos() = { -30, 185 };
	statusPointBtn["STR"]->SetEvent(bind(&Character::IncressStrength, character));

	statusPointBtn["DEX"] = new Button(Vector2(40, 40));
	statusPointBtn["DEX"]->SetTexture(L"Textures/UI/btn_levelup_up.png");
	statusPointBtn["DEX"]->SetDownTexture(L"Textures/UI/btn_levelup_down.png");
	statusPointBtn["DEX"]->Pos() = { -30, 90 };
	statusPointBtn["DEX"]->SetEvent(bind(&Character::IncressDexterity, character));

	statusPointBtn["VIT"] = new Button(Vector2(40, 40));
	statusPointBtn["VIT"]->SetTexture(L"Textures/UI/btn_levelup_up.png");
	statusPointBtn["VIT"]->SetDownTexture(L"Textures/UI/btn_levelup_down.png");
	statusPointBtn["VIT"]->Pos() = { -30, -35 };
	statusPointBtn["VIT"]->SetEvent(bind(&Character::IncressVitality, character));

	statusPointBtn["ENG"] = new Button(Vector2(40, 40));
	statusPointBtn["ENG"]->SetTexture(L"Textures/UI/btn_levelup_up.png");
	statusPointBtn["ENG"]->SetDownTexture(L"Textures/UI/btn_levelup_down.png");
	statusPointBtn["ENG"]->Pos() = { -30, -130 };
	statusPointBtn["ENG"]->SetEvent(bind(&Character::IncressEnergy, character));

}
