#include "Framework.h"

SpellManager::SpellManager()
{
	CreateSpells();
}

SpellManager::~SpellManager()
{
}

void SpellManager::Update()
{
	UpdateSpell(fireBolt);
	UpdateSpell(iceBolt);
	UpdateSpell(frozenOrb);
	UpdateSpell(diaLightning);
	UpdateSpell(diaNova);
}

void SpellManager::Render()
{
	RenderSpell(fireBolt);
	RenderSpell(iceBolt);
	RenderSpell(frozenOrb);
	RenderSpell(diaLightning);
	RenderSpell(diaNova);
	
}

float SpellManager::GetSpellMpPrice(string spellName)
{
	if (spellName == "FireBolt")
	{
		return fireBolt[0]->GetMpPrice();
	}
	if (spellName == "IceBolt")
	{
		return iceBolt[0]->GetMpPrice();
	}
	if (spellName == "FrozenOrb")
	{
		return frozenOrb[0]->GetMpPrice();
	}
	return 0.0f;
}

void SpellManager::ActiveSpell(string spellName, Vector2 pos, Vector2 direction)
{
	if (spellName == "FireBolt")
	{
		ActiveSpell(fireBolt, pos, direction);
	}
	if (spellName == "IceBolt")
	{
		ActiveSpell(iceBolt, pos, direction);
		//Audio::Get()->Play("IceBolt");
	}
	if (spellName == "FrozenOrb")
	{
		ActiveSpell(frozenOrb, pos, direction);
		Audio::Get()->Play("IceBolt");
	}
	if (spellName == "DiaLightning")
	{
		ActiveSpell(diaLightning, pos, direction);
	}
}

void SpellManager::ActiveSpellNova(string spellName, Vector2 pos)
{
	if (spellName == "DiaNova")
	{
		Audio::Get()->Play("Diablo_Nova");
		float theta = XM_2PI / 20;
		for (int i = 0; i < 20; i++)
		{
			if (diaNova[i]->Active()) continue;

			float x = cos(theta * i);
			float y = sin(theta * i);

			diaNova[i]->Fire(pos, { x, y });
		}
	}
}

void SpellManager::CollisionCharacter(Character* character)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (diaNova[i]->Active())
		{
			if (character->IsCollision(diaNova[i]->GetCollider(), diaNova[i]->GetSpellDamage()))
			{
				diaNova[i]->SetActive(false);
			}
		}
		if (diaLightning[i]->Active())
		{
			if(character->IsCollision(diaLightning[i]->GetCollider(), diaLightning[i]->GetSpellDamage()))
			{
				diaLightning[i]->SetActive(false);
			}
		}
	}
}

void SpellManager::CollisionMonsters(Monster* monster)
{
	// 화면 안에있는 놈들만 충돌처리한다 !
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (fireBolt[i]->Active())
		{
			if (monster->IsCollision(fireBolt[i]->GetCollider(), fireBolt[i]->GetSpellDamage()))
			{
				if (monster->GetIsDead())
				{
					player->SetExperience(monster->GetExperience());
				}
				fireBolt[i]->SetActive(false);
				EffectManager::Get()->Play("FireExplosion", fireBolt[i]->GlobalPos());
				Audio::Get()->Play("FireBolt");
			}
		}
		if (iceBolt[i]->Active())
		{
			if (monster->IsCollision(iceBolt[i]->GetCollider(), iceBolt[i]->GetSpellDamage()))
			{
				if (monster->GetIsDead())
				{
					player->SetExperience(monster->GetExperience());
				}
				iceBolt[i]->SetActive(false);
				EffectManager::Get()->Play("IceExplosion", iceBolt[i]->GlobalPos());
			}
		}
	}
}

void SpellManager::CreateSpells()
{
	for(int i = 0; i < POOL_SIZE; i++)
		CreateSpell(fireBolt, new FireBolt());
	for(int i = 0; i < POOL_SIZE; i++)
		CreateSpell(iceBolt, new IceBolt());
	for(int i = 0; i < POOL_SIZE; i++)
		CreateSpell(frozenOrb, new FrozenOrb());
	for(int i = 0; i < POOL_SIZE; i++)
		CreateSpell(diaLightning, new DiaLightning());
	for(int i = 0; i < POOL_SIZE; i++)
		CreateSpell(diaNova, new DiaNova());
}

template<class T>
void SpellManager::UpdateSpell(vector<T*> spells)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (spells[i]->Active())
		{
			spells[i]->Update();
		}
	}
}

template<class T>
void SpellManager::RenderSpell(vector<T*> spells)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (spells[i]->Active())
		{
			spells[i]->Render();
		}
	}
}

template<class T>
void SpellManager::ActiveSpell(vector<T*> spells, Vector2 pos, Vector2 direction)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (spells[i]->Active()) continue;

		spells[i]->Fire(pos, direction);
		break;
	}
}

template<class T>
void SpellManager::CreateSpell(vector<T*> &vec, T* className)
{
	vec.push_back(className);
}
