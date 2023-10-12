#include "Framework.h"

Sorceress_Cast::Sorceress_Cast(Transform* target)
	: Action(L"Textures/Sorceress/cast.png", 14, 16, false), target(target)
{
	//Action::SetFrameEvent(bind(&Sorceress_Cast::Cast, this), 14);
	//for(pair<string, Action*> casts : castAction)
	castAction["Fire"] = new Action(L"Textures/Spell/fireCast.png", 14, 1, false, 1.5f);
	castAction["Cold"] = new Action(L"Textures/Spell/iceCast.png", 16, 1, false, 2.0f);
	castAction["Lightning"] = new Action(L"Textures/Spell/lightningCast.png", 18, 1, false, 2.0f);
}

Sorceress_Cast::~Sorceress_Cast()
{
	for (pair<string, Action*> cast : castAction)
		delete cast.second;
}

void Sorceress_Cast::Update()
{
	Action::Update();
	castAction[castType]->Update();
}

void Sorceress_Cast::Render()
{
	Action::Render();
	castAction[castType]->Render();
}

void Sorceress_Cast::Start()
{
	Action::Start();
	castAction[castType]->Start();

	Audio::Get()->Play(castType + "Cast");
}

