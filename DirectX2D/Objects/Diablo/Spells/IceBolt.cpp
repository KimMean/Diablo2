#include "Framework.h"

IceBolt::IceBolt()
	: ColdSpell(L"Textures/UI/Spell/IceBolt_Up.png")
{
	action = new Action(L"Textures/Spell/IceBolt.png", 6, 16, true);

	collider = new CircleCollider(30.0f);
	collider->SetParent(this);

	action->Start();
}

IceBolt::~IceBolt()
{
	delete action;
	delete collider;
}

void IceBolt::Update()
{
	action->Update();
	Pos() += direction * speed * DELTA;
	UpdateWorld();
	collider->UpdateWorld();
	ColdSpell::Update();
}

void IceBolt::Render()
{
	SetRender();
	//Environment::Get()->SetAdditiveBlend();
	action->Render();
	//Environment::Get()->SetAlphaBlend();
	collider->Render();
	ColdSpell::Render();
}

void IceBolt::Fire(Vector2 pos, Vector2 direction)
{

	Pos() = pos;
	UpdateWorld();
	collider->UpdateWorld();
	direction.Normalize();
	this->direction = direction;;
	float angle = -direction.Angle() * 180 / XM_PI + 180;
	int idx = angle / 22.5f + 4;
	if (idx > 15) idx = idx - 16;
	curTime = 0;

	action->Start();
	action->SetAngleIndex(idx);

	isActive = true;
}
