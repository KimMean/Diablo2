#include "Framework.h"
#include "Diablo.h"

Diablo::Diablo()
{
	InitDiablo();
}

Diablo::~Diablo()
{
	for (pair<ActionType, Action*> action : actions)
		delete action.second;

	delete hitBox;
}

void Diablo::Update()
{
	actions[curAction]->SetAngleIndex(angleIndex);
	actions[curAction]->Update();

	if (isDead) return;
	Control();
	Monster::Update();

	if(CAM->ContainFrustum(GlobalPos(), hitBox->Size()))
		SpellManager::Get()->CollisionMonsters(this);
}

void Diablo::Render()
{
	SetRender();
	actions[curAction]->Render();
	hitBox->Render();
	Monster::Render();
}

void Diablo::PostRender()
{
	Monster::PostRender();
}

void Diablo::SetCurrentHelthPoint(float incressValue)
{
	Monster::SetCurrentHelthPoint(incressValue);
	if (curHelthPoint <= 0)
	{
		isDead = true;
		curAction = DEAD;
		actions[DEAD]->Start();
		Audio::Get()->Play("Diablo_Death");
	}
	else
	{
		SetAction(HIT);
	}
}

void Diablo::SetTarget(Transform* target)
{
	this->target = target;
	((Diablo_Lightning*)actions[LIGHTNING])->SetTarget(target);
	((Diablo_Fanaticism*)actions[FANATICISM])->SetTarget(target);
}

bool Diablo::IsCollision(Collider* collider, float damage)
{
	if (hitBox->IsCollision(collider))
	{
		if (damage > 0)
		{
			SetCurrentHelthPoint(-damage);
			Audio::Get()->Play("Diablo_Hit");
			// 체력깍기
		}
		return true;
	}
	return false;
}

bool Diablo::IsCollision(Vector2 pos)
{
	return hitBox->IsPointCollision(pos);
}

void Diablo::Control()
{
	switch (curState)
	{
	case Monster::PATROL:
		Patrol();
		break;
	case Monster::TRACE:
		Trace();
		break;
	case Monster::ATTACK:
		break;
	case Monster::HIT:
		break;
	case Monster::DEAD:
		break;
	}

	UpdateWorld();
	hitBox->UpdateWorld();

}

void Diablo::Move()
{
}

void Diablo::Attack()
{
}

void Diablo::Death()
{
	isActive = false;
}


void Diablo::Patrol()
{
	if (isPatrol)
	{
		MovePath();
		SetAction(WALK);
	}
	else
	{
		SetAction(IDLE);
		waitingTime += DELTA;
		if (waitingTime > PATROL_TIME)
		{
			waitingTime = 0.0f;
			UpdatePath(GlobalPos(), PATROL_RANGE);
			isPatrol = true;
		}
	}
	DetectionTarget();
}

void Diablo::Trace()
{
	if (!(curAction == WALK) && !(curAction == IDLE)) return;
	Monster::Trace();
	// 추적코드
	waitingTime += DELTA;
	attackDelay += DELTA;
	if (waitingTime > TRACE_TIME)
	{
		waitingTime = 0.0f;
		DetectionTarget();
	}
	if (attackDelay > 3.0f)
	{
		int rnd = Random(0, 2);
		switch (rnd)
		{
		case 0 :
			SetAction(LIGHTNING);
			break;
		case 1 :
			SetAction(FANATICISM);
			break;
		}
		attackDelay -= 3.0f;
	}
	else
	{
		SetAction(WALK);
	}
}

void Diablo::DetectionTarget()
{
	if (!target) return;

	if (IsCollisionTarget())
	{
		SetState(TRACE);
		UpdatePath(GlobalPos(), target->GlobalPos());
	}
	else
	{
		SetState(PATROL);
	}
}

void Diablo::SetIdle()
{
	curAction = IDLE;
	actions[IDLE]->Start();
}

void Diablo::SetAction(int type)
{
	if (curAction == type) return;
	if (curAction == DEAD) return;
	if (!(curAction == IDLE) && !(curAction == WALK)) return;

	actions[curAction]->Stop();
	curAction = (ActionType)type;
	actions[(ActionType)type]->Start();
}

void Diablo::InitDiablo()
{
	name = "Diablo";
	maxHelthPoint = 100.0f;
	curHelthPoint = maxHelthPoint;
	//Pos() = { CENTER_X, CENTER_Y };

	hitBox = new RectCollider(Vector2(80, 100));
	hitBox->SetParent(this);

	CreateActions();
	actions[curAction]->Start();
}

void Diablo::CreateActions()
{
	actions[IDLE] = new Diablo_Idle();
	actions[WALK] = new Diablo_Walk();
	actions[DEAD] = new Diablo_Death();
	actions[DEAD]->SetEvent(bind(&Diablo::Death, this));
	actions[RUN] = new Diablo_Run();
	actions[RUN]->SetEvent(bind(&Diablo::SetIdle, this));
	actions[HIT] = new Diablo_Hit();
	actions[HIT]->SetEvent(bind(&Diablo::SetIdle, this));
	actions[ATTACK] = new Diablo_Attack();
	actions[ATTACK]->SetEvent(bind(&Diablo::SetIdle, this));
	actions[LIGHTNING] = new Diablo_Lightning(this);
	actions[LIGHTNING]->SetEvent(bind(&Diablo::SetIdle, this));
	actions[FANATICISM] = new Diablo_Fanaticism(this);
	actions[FANATICISM]->SetEvent(bind(&Diablo::SetIdle, this));
}

void Diablo::SetState(State state)
{
	if (curState == state) return;

	waitingTime = 0.0f;
	curState = state;
	switch (curState)
	{
	case Monster::PATROL:
		SetAction(WALK);
		break;
	case Monster::TRACE:
		SetAction(WALK);
		break;
	case Monster::ATTACK:
		break;
	case Monster::HIT:
		SetAction(HIT);
		break;
	case Monster::DEAD:
		SetAction(DEAD);
		break;
	default:
		break;
	}
}
