#include "Framework.h"

SkillTree::SkillTree()
	: Panel(L"Textures/UI/Spell/skillTreeBG.png", Vector2(480, 640))
{
	SetPixelShader(L"SQRT.hlsl");
	Pos() = Vector2(WIN_WIDTH - GetSize().x * 0.5f, WIN_HEIGHT - GetSize().y * 0.5f);

	collider = new RectCollider(Vector2(480, 640));
	collider->SetParent(this);

	CreateSpellTree();

	UpdateWorld();
	collider->UpdateWorld();
}

SkillTree::~SkillTree()
{
	delete coldSpell;
	delete lightningSpell;
	delete fireSpell;
}

void SkillTree::Update()
{
	if (!Active()) return;

	Panel::Update();

	targetPanel->Update();

	coldBtn->Update();
	lightningBtn->Update();
	fireBtn->Update();
}

void SkillTree::Render()
{
	if (!Active()) return;
	Panel::Render();

	targetPanel->Render();

	coldBtn->Render();
	lightningBtn->Render();
	fireBtn->Render();


	Float2 pos = { GlobalPos().x -140, GlobalPos().y + 290 };
	Font::Get()->RenderText("ÄÝµå ½ºÆç", pos);

	pos.x += 140;
	Font::Get()->RenderText("¶óÀÌÆ®´× ½ºÆç", pos);

	pos.x += 140;
	Font::Get()->RenderText("ÆÄÀÌ¾î ½ºÆç", pos);

	collider->Render();

}

void SkillTree::CreateSpellTree()
{
	coldSpell = new ColdSpellTree();
	coldSpell->SetParent(this);
	coldSpell->UpdateWorld();

	lightningSpell = new LightningSpellTree();
	lightningSpell->SetParent(this);
	lightningSpell->UpdateWorld();

	fireSpell = new FireSpellTree();
	fireSpell->SetParent(this);
	fireSpell->UpdateWorld();

	targetPanel = coldSpell;
	targetPanel->SetActive(true);

	CreateSpellBtn(coldBtn, { -140, 290 });
	CreateSpellBtn(lightningBtn, { 0, 290 });
	CreateSpellBtn(fireBtn, { 140, 290 });

	coldBtn->SetEvent(bind(&SkillTree::ClickColdBtn, this));
	lightningBtn->SetEvent(bind(&SkillTree::ClickLightningBtn, this));
	fireBtn->SetEvent(bind(&SkillTree::ClickFireBtn, this));
}

void SkillTree::CreateSpellBtn(Button*& btn, Vector2 pos)
{
	btn = new Button(Vector2(140, 40));
	btn->SetTexture(L"Textures/AlphaTexture.png");
	btn->SetParent(this);
	btn->Pos() += pos;
}

void SkillTree::ChangeTargetPanel(Panel* panel)
{
	targetPanel->SetActive(false);
	targetPanel = panel;
	targetPanel->SetActive(true);
}
