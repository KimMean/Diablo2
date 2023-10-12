#include "Framework.h"

FireBolt::FireBolt()
	: FireSpell(L"Textures/UI/Spell/FireBolt_Up.png")
{
	action = new Action(L"Textures/Spell/fireBall.png", 5, 16, true);

	collider = new CircleCollider(30.0f);
	collider->SetParent(this);

	action->Start();

}

FireBolt::~FireBolt()
{
	delete action;
	delete collider;
}

void FireBolt::Update()
{
	action->Update();
	Pos() += direction * speed * DELTA;
	UpdateWorld();
	collider->UpdateWorld();
	FireSpell::Update();
}

void FireBolt::Render()
{
	SetRender();
	Environment::Get()->SetAdditiveBlend();
	action->Render();
	Environment::Get()->SetAlphaBlend();
	collider->Render();
	FireSpell::Render();
}

void FireBolt::Fire(Vector2 pos, Vector2 direction)
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
