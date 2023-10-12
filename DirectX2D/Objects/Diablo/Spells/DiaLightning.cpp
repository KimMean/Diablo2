#include "Framework.h"

DiaLightning::DiaLightning()
{
	action = new Action(L"Textures/Effects/Lightning.png", 15, 8, true);

	collider = new CircleCollider(30.0f);
	collider->SetParent(this);

	action->Start();
}

DiaLightning::~DiaLightning()
{
	delete action;
	delete collider;
}

void DiaLightning::Update()
{
	action->Update();
	Pos() += direction * speed * DELTA;
	UpdateWorld();
	collider->UpdateWorld();
	Spell::Update();
}

void DiaLightning::Render()
{
	SetRender();
	Environment::Get()->SetAdditiveBlend();
	action->Render();
	Environment::Get()->SetAlphaBlend();
	collider->Render();
	Spell::Render();
}

void DiaLightning::Fire(Vector2 pos, Vector2 direction)
{

	Pos() = pos;
	UpdateWorld();
	collider->UpdateWorld();
	direction.Normalize();
	this->direction = direction;;
	float angle = -direction.Angle() * 180 / XM_PI + 180;
	int idx = angle / 45.0f + 2;
	if (idx > 7) idx = idx - 8;
	curTime = 0;
	action->Start();
	action->SetAngleIndex(idx);

	isActive = true;
}
