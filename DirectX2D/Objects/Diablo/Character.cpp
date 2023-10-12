#include "Framework.h"

Character::Character()
{
    inventory = new Inventory();
    status = new Status();
    skillTree = new SkillTree();
    basicUI = new BasicUI();
    basicUI->SetActive(true);

    status->SetCharacter(this);
    SetExperience(0);
    //inventory->Pos() = Vector2(WIN_WIDTH - inventory->GetSize().x * 0.5f, WIN_HEIGHT - inventory->GetSize().y * 0.5f);
    //inventory->Show(Vector2(WIN_WIDTH - inventory->GetSize().x * 0.5f, WIN_HEIGHT - inventory->GetSize().y * 0.5f))
}

Character::~Character()
{
    delete inventory;
    delete status;
    delete skillTree;
    delete basicUI;
}

void Character::Update()
{
    if (KEY_DOWN('1'))
        SetCurrentHelthPoint(10);
    if (KEY_DOWN('2'))
        SetCurrentMagicPoint(10);
    if (KEY_DOWN('I'))
    {
        inventory->SetActive(!inventory->ActiveSelf());
    }
    if (KEY_DOWN('C'))
    {
        status->SetActive(!status->ActiveSelf());
    }
    if (KEY_DOWN('T'))
    {
        skillTree->SetActive(!skillTree->ActiveSelf());
    }
    if (KEY_DOWN('U'))
    {
        LevelUP();
    }

    if (KEY_DOWN(VK_LBUTTON))
    {
        bool isPanel = false;

        if (inventory->Active() && inventory->GetCollider()->IsPointCollision(mousePos))
            isPanel = true;
        if (status->Active() && status->GetCollider()->IsPointCollision(mousePos))
            isPanel = true;
        if (skillTree->Active() && skillTree->GetCollider()->IsPointCollision(mousePos))
            isPanel = true;

        
        if(!isPanel)
        {
            int start = AStar::Get()->FindCloseNode(GlobalPos());
            int end = AStar::Get()->FindCloseNode(CAM->ScreenToWorld(mousePos));

            AStar::Get()->GetPath(start, end, GetPath());
        }
    }
    SetCurrentHelthPoint(10 * DELTA);
    SetCurrentMagicPoint(10 * DELTA);
    SetCurrentStamina(10 * DELTA);

    inventory->Update();
    status->Update();
    skillTree->Update();
    basicUI->Update();
}

void Character::Render()
{
}

void Character::PostRender()
{
    inventory->Render();
    status->Render();
    skillTree->Render();
    basicUI->Render();

    int curPoint = curHelthPoint;
    int maxPoint = maxHelthPoint;
    Font::Get()->RenderText((to_string(curPoint) + "/" + to_string(maxPoint)), {100, 170});

    curPoint = curMagicPoint;
    maxPoint = maxMagicPoint;
    Font::Get()->RenderText((to_string(curPoint) + "/" + to_string(maxPoint)), {WIN_WIDTH - 100, 170 });
}

void Character::SetCurrentHelthPoint(float incressValue)
{
    curHelthPoint += incressValue;
    if (curHelthPoint >= maxHelthPoint)
        curHelthPoint = maxHelthPoint;
    else if (curHelthPoint < 0)
    {
        curHelthPoint = 0;
    }

    float amount = curHelthPoint / maxHelthPoint;

    basicUI->SetHelthPointValue(amount);
}

void Character::SetCurrentMagicPoint(float incressValue)
{
    curMagicPoint += incressValue;
    if (curMagicPoint >= maxMagicPoint)
        curMagicPoint = maxMagicPoint;
    else if (curMagicPoint < 0)
    {
        curMagicPoint = 0;
    }

    float amount = curMagicPoint / maxMagicPoint;

    basicUI->SetMagicPointValue(amount);
}

void Character::SetCurrentStamina(float incressValue)
{
    curStamina += incressValue;
    if (curStamina >= maxStamina)
        curStamina = maxStamina;
    else if (curStamina < 0)
    {
        curStamina = 0;
    }

    float amount = curStamina / maxStamina;

    basicUI->SetStaminaValue(amount);
}

void Character::SetExperience(float incressValue)
{
    experience += incressValue;
    if (experience >= maxExperience)
    {
        experience -= maxExperience;
        LevelUP();
    }
    else if (experience < 0)
    {
        experience = 0;
    }

    float amount = experience / maxExperience;

    basicUI->SetExperienceValue(amount);
}

void Character::SetAngleIndex(float angle)
{
    int idx = angle / 22.5f + 4;
    if (idx > 15) idx = idx - 16;
    angleIndex = idx;
}

void Character::MovePath()
{
    //if (path.empty())
    //    return;

    Vector2 direction = path.back() - Pos();
    //Rot().z = direction.Angle();

    float angle = -direction.GetNormalized().Angle() * 180 / XM_PI + 180;
    SetAngleIndex(angle);
    Pos() += direction.GetNormalized() * moveSpeed * DELTA;

    if (direction.Length() < 5.0f)
        path.pop_back();
}

void Character::LevelUP()
{
    level++;
    if (level >= 99) 
    {
        level = 99;
        return;
    }
    statusPoint += 5;
    skillPoint++;
}

void Character::IncressStrength()
{
    if(statusPoint > 0)
    {
        strength++;
        statusPoint--;
    }

}

void Character::IncressDexterity()
{
    if (statusPoint > 0)
    {
        dexterity++;
        statusPoint--;
    }
}

void Character::IncressVitality()
{
    if (statusPoint > 0)
    {
        vitality++;
        statusPoint--;
        SetMaxHelthPoint(5);
        SetMaxStaminaPoint(5);
    }
}

void Character::IncressEnergy()
{
    if (statusPoint > 0)
    {
        energy++;
        statusPoint--;
        SetMaxMagicPoint(5);
    }
}

void Character::SetMaxHelthPoint(UINT value)
{
    maxHelthPoint += value;
}

void Character::SetMaxMagicPoint(UINT value)
{
    maxMagicPoint += value;
}

void Character::SetMaxStaminaPoint(UINT value)
{
    maxStamina += value;
}

