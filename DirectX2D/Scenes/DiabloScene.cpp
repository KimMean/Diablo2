#include "Framework.h"
#include "DiabloScene.h"

bool DebugMode;

DiabloScene::DiabloScene()
{
	map = new Map();
	AStar::Get()->SetTileMap(map);
	player = new Sorceress();
	diablos.resize(100);
	for (Diablo*& diablo : diablos)
	{
		diablo = new Diablo();
		diablo->SetTarget(player);
		//diablo->Pos() = { CENTER_X, CENTER_Y };
		diablo->Pos() = AStar::Get()->GetRandomNodePos();
	}
	SpellManager::Get()->SetPlayer(player);
	EffectManager::Get()->Add("IceExplosion", 50, L"Textures/Spell/iceExplosion.png", 16, 1, 2.0f);
	EffectManager::Get()->Add("FireExplosion", 50, L"Textures/Spell/fireExplosion.png", 16, 1, 2.0f);

	CreateSound();

	SetFont();
	CAM->SetTarget(player);
}

DiabloScene::~DiabloScene()
{
	AStar::Delete();
	delete map;
	delete player;
	for (Diablo* diablo : diablos)
		delete diablo;
	SpellManager::Delete();
	EffectManager::Delete();
}

void DiabloScene::Update()
{
	if (KEY_DOWN(VK_TAB))
	{
		DebugMode = !DebugMode;
	}

	map->Update();
	//AStar::Get()->Update();
	player->Update();
	for (Diablo* diablo : diablos)
	{
		if(diablo->Active())
		{
			diablo->Update();
		}
	}
	SpellManager::Get()->Update();
	EffectManager::Get()->Update();
}

void DiabloScene::Render()
{
	map->Render();
	if(KEY_PRESS('A'))
		AStar::Get()->Render();
	player->Render();
	for (Diablo* diablo : diablos)
	{
		if (diablo->Active())
		{
			if (CAM->ContainFrustum(diablo->GlobalPos(), { 80, 100 }))
			{
				diablo->Render();
			}
		}
	}
	SpellManager::Get()->Render();
	EffectManager::Get()->Render();
}

void DiabloScene::PostRender()
{
	player->PostRender();
	player->RenderUI();

	for (Diablo* diablo : diablos)
	{
		if (diablo->IsCollision(CAM->ScreenToWorld(mousePos)))
		{
			if (diablo->Active())
				diablo->PostRender();
		}
	}
}

void DiabloScene::CreateSound()
{
	Audio::Get()->Add("Background", "Sounds/catacom.mp3", true, true);

	Audio::Get()->Add("ColdCast", "Sounds/Character/coldCast.mp3");
	Audio::Get()->Add("FireCast", "Sounds/Character/fireCast.mp3");
	Audio::Get()->Add("LightningCast", "Sounds/Character/lightningCast.mp3");

	Audio::Get()->Add("Diablo_Hit", "Sounds/Monster/diablo_hit.mp3");
	Audio::Get()->Add("Diablo_Death", "Sounds/Monster/diablo_death.mp3");
	Audio::Get()->Add("Diablo_Laugh", "Sounds/Monster/diablo_laugh.mp3");
	Audio::Get()->Add("Diablo_Nova", "Sounds/Monster/diablo_skill1.mp3");
	Audio::Get()->Add("Diablo_Lightning", "Sounds/Monster/diablo_skill2.mp3");

	Audio::Get()->Add("FireBolt", "Sounds/Spell/fireBolt.mp3");
	Audio::Get()->Add("IceBolt", "Sounds/Spell/iceBolt.mp3");
	Audio::Get()->Add("Teleport", "Sounds/Spell/teleport.mp3");
	
	Audio::Get()->Add("Button", "Sounds/UI/button.mp3");
	Audio::Get()->Add("Helm", "Sounds/UI/items/helm.mp3");
	Audio::Get()->Add("Armor", "Sounds/UI/items/armor.mp3");
	Audio::Get()->Add("Belt", "Sounds/UI/items/belt.mp3");
	Audio::Get()->Add("Glove", "Sounds/UI/items/glove.mp3");
	Audio::Get()->Add("Boots", "Sounds/UI/items/boots.mp3");
	Audio::Get()->Add("Wand", "Sounds/UI/items/wand.mp3");

	Audio::Get()->Play("Background");
}


void DiabloScene::SetFont()
{
	Font::Get()->AddColor("White", 1, 1, 1);
	Font::Get()->AddStyle("DiabloEng", L"Diablo Light");
	Font::Get()->AddStyle("DiabloKor", L"Kodia");
	Font::Get()->AddStyle("DiabloKor_30", L"Kodia", 30.0f);

	Font::Get()->SetColor("White");
	Font::Get()->SetStyle("DiabloKor");
}
