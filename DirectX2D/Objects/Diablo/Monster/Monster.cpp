#include "Framework.h"

Monster::Monster()
{
	traceCollider = new CircleCollider(TRACE_RANGE);
	traceCollider->SetParent(this);
	InitMonster();
}

Monster::~Monster()
{
	delete traceCollider;
	delete hpBar;
}

void Monster::Update()
{
	traceCollider->UpdateWorld();
}

void Monster::Render()
{
	traceCollider->Render();
}

void Monster::PostRender()
{
	hpBar->Render();
	Font::Get()->SetStyle("DiabloKor_30");
	Font::Get()->RenderText(name, { CENTER_X - 15.0f , WIN_HEIGHT - 45.0f });
	Font::Get()->SetStyle("DiabloKor");
}

void Monster::SetCurrentHelthPoint(float incressValue)
{
	curHelthPoint += incressValue;
	if (curHelthPoint >= maxHelthPoint)
		curHelthPoint = maxHelthPoint;
	else if (curHelthPoint < 0)
	{
		curHelthPoint = 0;
	}

	float amount = curHelthPoint /maxHelthPoint;

	hpBar->SetAmount(amount);
}

void Monster::Patrol()
{
	// ¼øÂûÄÚµå
	

	//DetectionTarget();
}

void Monster::Trace()
{
	MovePath();
}


bool Monster::IsCollisionTarget()
{
	if (traceCollider->IsPointCollision(target->GlobalPos()))
		return true;
	return false;
}

void Monster::SetAngleIndex(float angle)
{
	int idx = angle / 45.0f + 2;
	if (idx > 7) idx = idx - 8;
	angleIndex = idx;
}

void Monster::InitMonster()
{
	hpBar = new Progress(L"Textures/UI/monsterHP.png");
	hpBar->SetBackImage(L"Textures/UI/monsterHP_bg.png");
	hpBar->SetResizeTexture(hpBar->GetSize() * 1.5f);
	hpBar->GetBackImage()->SetResizeTexture(hpBar->GetBackImage()->GetSize() * 1.5f);
	hpBar->Pos() = { CENTER_X , WIN_HEIGHT - hpBar->GetBackImage()->GetSize().y };
	hpBar->SetParent(this);
	hpBar->UpdateWorld();
	hpBar->GetBackImage()->UpdateWorld();
}

void Monster::MovePath()
{
	if (path.empty())
	{
		isPatrol = false;
		return;
	}

	Vector2 direction = path.back() - Pos();
	//Rot().z = direction.Angle();

	float angle = -direction.GetNormalized().Angle() * 180 / XM_PI + 180;
	SetAngleIndex(angle);
	Pos() += direction.GetNormalized() * speed * DELTA;

	if (direction.Length() < 5.0f)
		path.pop_back();
}

void Monster::UpdatePath(Vector2 pos, Vector2 targetPos)
{
	int start = AStar::Get()->FindCloseNode(pos);
	int end = AStar::Get()->FindCloseNode(targetPos);
	AStar::Get()->GetPath(start, end, path);
}

void Monster::UpdatePath(Vector2 pos, float range)
{
	int start = AStar::Get()->FindCloseNode(pos);
	int end = AStar::Get()->FindRandomPos(pos, range);
	AStar::Get()->GetPath(start, end, path);
}
