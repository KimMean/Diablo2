#include "Framework.h"

Sorceress::Sorceress()
{
    tag = "Sorceress";
    CreateActions();
    actions[curAction]->Start();

    Pos() = { CENTER_X, CENTER_Y };

    collider = new RectCollider(Vector2(30, 60));
    collider->SetParent(this);
    //test = new Quad(L"Textures/Sorceress/idle.png");

    moveSpeed = 200.0f;

    CreateSpells();
    //bolt = new IceBolt();
}

Sorceress::~Sorceress()
{
    for (pair<ActionType, Action*> action : actions)
        delete action.second;
    for (pair<string, Spell*> spell : spells)
        delete spell.second;
    //delete bolt;
}

void Sorceress::Update()
{
    actions[curAction]->SetAngleIndex(angleIndex);
    actions[curAction]->Update();
    
    Control();
    SpellManager::Get()->CollisionCharacter(this);

    Character::Update();
    UpdateWorld();
    collider->UpdateWorld();

    //bolt->Update();
}

void Sorceress::Render()
{
    
    SetRender();
    Character::Render();
    actions[curAction]->Render();
    collider->Render();
    //test->Render();
    //bolt->Render();
}

void Sorceress::PostRender()
{
    Character::PostRender();

    //string fps = "Angle : " + to_string(angleIndex) ;
    //Font::Get()->RenderText(fps, { 150, WIN_HEIGHT - 40 });
}

void Sorceress::SetSpell(string spellName, bool isLeftSpell)
{
}

void Sorceress::ActiveSpell()
{
    float price = SpellManager::Get()->GetSpellMpPrice(spellName);

    if (price > curMagicPoint) return;

    SetCurrentMagicPoint(-price);

    SpellManager::Get()->ActiveSpell(spellName, GlobalPos(), direction);
    if (spellName == "Teleport")
    {
        Audio::Get()->Play("Teleport");
        Pos() = AStar::Get()->GetNodePos(CAM->ScreenToWorld(mousePos));
        UpdateWorld();
    }
}

bool Sorceress::IsCollision(Collider* collider, float damage)
{
    if (this->collider->IsCollision(collider))
    {
        if (damage > 0)
        {
            SetCurrentHelthPoint(-damage);
            if (curAction != CAST)
                SetAction(HIT);
            // 체력깍기
        }
        return true;
    }
    return false;
}

void Sorceress::SetCurrentHelthPoint(float incressValue)
{
    Character::SetCurrentHelthPoint(incressValue);
    if (curHelthPoint <= 0)
    {
        // 주금
    }
    else
    {
    }
}

void Sorceress::SetCurrentMagicPoint(float incressValue)
{
    Character::SetCurrentMagicPoint(incressValue);
}

void Sorceress::SetCurrentStamina(float incressValue)
{
    Character::SetCurrentStamina(incressValue);
}

void Sorceress::SetExperience(float incressValue)
{
    Character::SetExperience(incressValue);
}

void Sorceress::Control()
{
    Move();

    if (KEY_DOWN(MK_RBUTTON))
    {
        bool isPanel = false;
        if (inventory->Active() && inventory->GetCollider()->IsPointCollision(mousePos))
            isPanel = true;
        if (status->Active() && status->GetCollider()->IsPointCollision(mousePos))
            isPanel = true;
        if (skillTree->Active() && skillTree->GetCollider()->IsPointCollision(mousePos))
            isPanel = true;

        if(!isPanel && spellName != "")
            Attack();
    }
    if(curAction != CAST)
        SelectSpell();
    
}

void Sorceress::Move()
{
    if (curAction == CAST || curAction == HIT) return;
    if (path.empty())
    {
        SetAction(IDLE);
        return;
    }

    SetAction(RUN);
    SetCurrentStamina(-20 * DELTA);
    MovePath();
}

void Sorceress::Attack()
{
    direction = (CAM->ScreenToWorld(mousePos) - GlobalPos()).GetNormalized();
    float angle = -direction.Angle() * 180 / XM_PI + 180;
    SetAngleIndex(angle);

    SetAction(CAST);
    path.clear();

    //SpellManager::Get()->ActiveSpell("FireBolt", GlobalPos(), direction);
    //SpellManager::Get()->ActiveSpell("IceBolt", GlobalPos(), direction);
}

void Sorceress::SelectSpell()
{
    if (KEY_DOWN(VK_F1))
    {
        basicUI->SetRightSpell(Texture::Add(L"Textures/UI/Spell/FireBolt_Up.png"));
        spellName = "FireBolt";
        ((Sorceress_Cast*)actions[CAST])->SetCastType("Fire");
    }
    if (KEY_DOWN(VK_F2))
    {
        basicUI->SetRightSpell(Texture::Add(L"Textures/UI/Spell/IceBolt_Up.png"));
        spellName = "IceBolt";
        ((Sorceress_Cast*)actions[CAST])->SetCastType("Cold");
    }
    if (KEY_DOWN(VK_F3))
    {
        basicUI->SetRightSpell(Texture::Add(L"Textures/UI/Spell/FrozenOrb_Up.png"));
        spellName = "FrozenOrb";
        ((Sorceress_Cast*)actions[CAST])->SetCastType("Cold");
    }
    if (KEY_DOWN(VK_F4))
    {
        basicUI->SetRightSpell(Texture::Add(L"Textures/UI/Spell/Teleport_Up.png"));
        spellName = "Teleport";
        ((Sorceress_Cast*)actions[CAST])->SetCastType("Lightning");
    }
}

void Sorceress::CreateActions()
{
    actions[IDLE] = new Sorceress_Idle(this);
    actions[WALK] = new Sorceress_Walk(this);
    actions[RUN] = new Sorceress_Run(this);
    actions[CAST] = new Sorceress_Cast(this);
    actions[CAST]->SetEvent(bind(&Sorceress::SetIdle, this));
    actions[CAST]->SetFrameEvent(bind(&Sorceress::ActiveSpell, this), 8);
    actions[HIT] = new Sorceress_Hit(this);
    actions[HIT]->SetEvent(bind(&Sorceress::SetIdle, this));
}

void Sorceress::SetIdle()
{
    SetAction(IDLE);
}

void Sorceress::SetAction(int type)
{
    if (curAction == type) return;

    curAction = (ActionType)type;
    actions[(ActionType)type]->Start();
}

void Sorceress::CreateSpells()
{
    spells["FireBolt"] = new FireBolt();
}
