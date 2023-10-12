#include "Framework.h"

Item::Item(wstring texture, Vector2 SlotSize)
	: Button(texture)
{
	slotSize = SlotSize;
	collider = new RectCollider(GetTexture()->GetSize());
	collider->SetParent(this);
	SetEvent(bind(&Item::OnClick, this));
}

Item::~Item()
{
	delete collider;
	delete description;
}

void Item::Update()
{
	Button::Update();

	if(!isDrag)
	{
		Vector2 pos = Pos();
		if (GetCollider()->IsPointCollision(mousePos))
		{
			ShowDescription(true);
		}
		else
		{
			ShowDescription(false);
		}
	}
}

void Item::Render()
{
	Button::Render();
	if(showDescription)
		description->Render();
	collider->Render();
}

void Item::OnClick()
{
	if (!inven) return;

	switch (type)
	{
	case Item::HEAD:
		Audio::Get()->Play("Helm");
		break;
	case Item::BODY:
		Audio::Get()->Play("Armor");
		break;
	case Item::BELT:
		Audio::Get()->Play("Belt");
		break;
	case Item::BOOTS:
		Audio::Get()->Play("Boots");
		break;
	case Item::GLOVE:
		Audio::Get()->Play("Glove");
		break;
	case Item::WEAPON:
	case Item::SUB_WEAPON:
		Audio::Get()->Play("Wand");
		break;
	default:
		break;
	}

	if (isDrag)
	{
		isDrag = false;
		return;
	}
	isDrag = true;
	inven->SetTargetItem(this);
	ShowDescription(false);
}

void Item::SetDescription(wstring texture)
{
	description = new Quad(texture);
	description->SetParent(this);
	description->Pos() = Pos() + Vector2(-50, 50);
	ShowDescription(false);
	description->UpdateWorld();
}

void Item::ShowDescription(bool isActive)
{
	//description->Pos() = Pos();
	description->UpdateWorld();
	showDescription = isActive;
	//description->SetActive(isActive);
}
