#include "Framework.h"

Inventory::Inventory()
	: Panel(L"Textures/UI/Inventory/Inventory.png", Vector2(480, 640))
{
	Pos() = Vector2(WIN_WIDTH - GetSize().x * 0.5f, WIN_HEIGHT - GetSize().y * 0.5f);
	//head = new Quad(L"Textures/UI/Inventory/HelmSlot.png");
	collider = new RectCollider(Vector2(480, 640));
	collider->SetParent(this);

	CreateSlot();
	CreateInventorySlot();
	CreateItems();

	cancelBtn = new Button(Vector2(45, 45));
	cancelBtn->SetTexture(L"Textures/UI/btn_cancel_up.png");
	cancelBtn->SetDownTexture(L"Textures/UI/btn_cancel_down.png");
	cancelBtn->Pos() = { -188, -273 };
	cancelBtn->SetParent(this);
	cancelBtn->SetEvent(bind(&Inventory::Hide, this));
	//head = new Quad(Vector2(90, 90));
	//head->SetTexture(L"Textures/UI/Inventory/HelmSlot.png");
	//head->Pos() = { 5, 275 };
	//head->SetParent(this);

	UpdateWorld();
	collider->UpdateWorld();
	for (pair<string, Quad*> slot : slots)
	{
		slot.second->SetParent(this);
		slot.second->UpdateWorld();
	}
	//head->UpdateWorld();
	
}

Inventory::~Inventory()
{
	for (pair<string, Quad*> slot : slots)
	{
		delete slot.second;
	}

	for (InventorySlot* slot : inventorySlots)
		delete slot;

	for (pair<string, Item*> item : items)
	{
		delete item.second;
	}
	delete cancelBtn;
}

void Inventory::Update()
{
	if (!Active()) return;

	for (pair<string, Item*> item : items)
	{
		item.second->Update();
	}

	for (pair<string, Quad*> slot : slots)
	{
		slot.second->GetColor() = COLOR_WHITE;
	}

	for (InventorySlot* slot : inventorySlots)
		slot->GetColor() = COLOR_TRANS;

	DragAndDrop();

	if (KEY_DOWN(MK_RBUTTON))
	{
		for (pair<string, Item*> item : items)
		{
			if(item.second->GetCollider()->IsPointCollision(mousePos))
			{
				bool isSame = false;
				for (pair<string, Quad*> slot : slots)
				{
					switch (item.second->GetItemType())
					{
					case Item::ItemType::HEAD:
						if (slot.first == "Helm") isSame = true;
						break;
					case Item::ItemType::BODY:
						if (slot.first == "Armor") isSame = true;
						break;
					case Item::ItemType::BELT:
						if (slot.first == "Belt") isSame = true;
						break;
					case Item::ItemType::GLOVE:
						if (slot.first == "Glove") isSame = true;
						break;
					case Item::ItemType::BOOTS:
						if (slot.first == "Boots") isSame = true;
						break;
					case Item::ItemType::WEAPON:
					case Item::ItemType::SUB_WEAPON:
						if (slot.first == "Weapon") isSame = true;
						break;
					}
					if (isSame)
					{
						item.second->Pos() = Pos() + slot.second->Pos();
						break;
					}
				}
			}
		}
	}
	//Panel::Update();
	//head->UpdateWorld();
	//UpdateWorld();
	cancelBtn->Update();
}

void Inventory::Render()
{
	if (!Active()) return;
	Panel::Render();
	for (pair<string, Quad*> slot : slots)
	{
		slot.second->Render();
	}

	for (InventorySlot* slot : inventorySlots)
		slot->Render();

	for (pair<string, Item*> item : items)
	{
		item.second->Render();
	}

	cancelBtn->Render();
	collider->Render();
	//head->Render();
}

void Inventory::Hide()
{
	isActive = false;
}

void Inventory::DragAndDrop()
{
	if (!target) return;
	
	target->Pos() = mousePos;
	for (int i = 0; i < inventorySlots.size(); i++)
	{
		if (inventorySlots[i]->GetCollider()->IsPointCollision(mousePos))
		{
			if (IsMountable(target, i))
			{
				if (KEY_DOWN(MK_LBUTTON))
				{
					Vector2 itemSize = target->GetSlotSize();
					Vector2 centerPos = inventorySlots[i]->Pos() -
						(inventorySlots[i]->Pos() - inventorySlots[i + (itemSize.y - 1) * INVENTORY_SLOT_SIZE.x + (itemSize.x - 1)]->Pos()) / 2;
					target->Pos() = centerPos;
					target = nullptr;
					for (int z = 0; z < itemSize.y; z++)
					{
						for (int j = 0; j < itemSize.x; j++)
						{
							inventorySlots[i + (z * INVENTORY_SLOT_SIZE.x) + j]->SetIsEmpty(false);
						}
					}
					break;
				}
			}
		}
	}

	if (!target) return;
	bool isSame = false;
	for (pair<string, Quad*> slot : slots)
	{
		if (target->GetCollider()->IsPointCollision(Pos() + slot.second->Pos()))
		{
			switch (target->GetItemType())
			{
			case Item::ItemType::HEAD:
				if (slot.first == "Helm") isSame = true;
				break;
			case Item::ItemType::BODY:
				if (slot.first == "Armor") isSame = true;
				break;
			case Item::ItemType::BELT:
				if (slot.first == "Belt") isSame = true;
				break;
			case Item::ItemType::GLOVE:
				if (slot.first == "Glove") isSame = true;
				break;
			case Item::ItemType::BOOTS:
				if (slot.first == "Boots") isSame = true;
				break;
			case Item::ItemType::WEAPON:
			case Item::ItemType::SUB_WEAPON:
				if (slot.first == "Weapon") isSame = true;
				else if (slot.first == "SubWeapon") isSame = true;
				break;
			}
			if (isSame)
			{
				slot.second->GetColor() = COLOR_BLUE;
				if (KEY_DOWN(MK_LBUTTON))
				{
					target->Pos() = Pos() + slot.second->Pos();
					target = nullptr;
					break;
				}
			}
			else 
			{
				slot.second->GetColor() = COLOR_RED;
			}
		}
	}

	
}

bool Inventory::IsMountable(Item* item, int slotIndex)
{
	Vector2 itemSize = item->GetSlotSize();
	int y = slotIndex / (int)INVENTORY_SLOT_SIZE.x;
	int x = slotIndex % (int)INVENTORY_SLOT_SIZE.x;
	bool isMount = true;

	for (int i = 0; i < itemSize.y; i++)
	{
		for (int j = 0; j < itemSize.x; j++)
		{
			int idx = slotIndex + (i * INVENTORY_SLOT_SIZE.x) + j;

			if (idx >= inventorySlots.size())
			{
				isMount = false;
				continue;
			}

			if (inventorySlots[idx]->IsEmpty())
			{
				inventorySlots[idx]->GetColor() = COLOR_BLUE;
			}
			else
			{
				inventorySlots[idx]->GetColor() = COLOR_RED;
				isMount = false;
			}
		}
	}

	return isMount;
}

void Inventory::SetTargetItem(Item* item)
{
	if (target) return;

	for (InventorySlot* slot : inventorySlots)
	{
		if (slot->GetCollider()->IsCollision(item->GetCollider()))
		{
			slot->SetIsEmpty(true);
		}
	}

	target = item;
}

bool Inventory::GetItem(Item* item)
{
	Vector2 itemSize = item->GetSlotSize();


	for (int y = 0; y < INVENTORY_SLOT_SIZE.y - itemSize.y + 1; y++)
	{
		for (int x = 0; x < INVENTORY_SLOT_SIZE.x - itemSize.x + 1; x++)
		{
			bool isAvailable = true;
			int idx = y * INVENTORY_SLOT_SIZE.x + x;

			for (int i = 0; i < itemSize.y; i++)
			{
				for (int j = 0; j < itemSize.x; j++)
				{
					if (!inventorySlots[idx + (i * INVENTORY_SLOT_SIZE.x) + j]->IsEmpty())
					{
						isAvailable = false;
					}
				}
			}

			if (isAvailable)
			{
				Vector2 centerPos = inventorySlots[idx]->Pos() -
					(inventorySlots[idx]->Pos() - inventorySlots[idx + (itemSize.y - 1) * INVENTORY_SLOT_SIZE.x + (itemSize.x - 1)]->Pos()) / 2;
				item->Pos() = centerPos;

				for (int i = 0; i < itemSize.y; i++)
				{
					for (int j = 0; j < itemSize.x; j++)
					{
						inventorySlots[idx + (i * INVENTORY_SLOT_SIZE.x) + j]->SetIsEmpty(false);
					}
				}
				return true;
			}
		}
	}

	return false;
}

bool Inventory::IsDrop(Item* item)
{
	return false;
}

void Inventory::CreateSlot()
{
	slots["Helm"] = new Quad(Vector2(85, 85));
	slots["Helm"]->SetTexture(L"Textures/UI/Inventory/HelmSlot.png");
	slots["Helm"]->Pos() = { 5, 275 };
	slots["Helm"]->SetPixelShader(L"Slot.hlsl");
	//slots["Helm"]->SetParent(this);

	slots["Weapon"] = new Quad(Vector2(85, 170));
	slots["Weapon"]->SetTexture(L"Textures/UI/Inventory/WeaponSlot.png");
	slots["Weapon"]->Pos() = { -170, 167 };
	slots["Weapon"]->SetPixelShader(L"Slot.hlsl");
	//slots["Weapon"]->SetParent(this);

	slots["Armor"] = new Quad(Vector2(85, 130));
	slots["Armor"]->SetPixelShader(L"Slot.hlsl");
	slots["Armor"]->SetTexture(L"Textures/UI/Inventory/ArmorSlot.png");
	slots["Armor"]->Pos() = { 5, 150 };
	//slots["Armor"]->SetParent(this);

	slots["SubWeapon"] = new Quad(Vector2(85, 170));
	slots["SubWeapon"]->SetTexture(L"Textures/UI/Inventory/WeaponSlot.png");
	slots["SubWeapon"]->Pos() = { 175, 167 };
	slots["SubWeapon"]->SetPixelShader(L"Slot.hlsl");
	//slots["SubWeapon"]->SetParent(this);

	slots["Glove"] = new Quad(Vector2(85, 85));
	slots["Glove"]->SetTexture(L"Textures/UI/Inventory/GloveSlot.png");
	slots["Glove"]->Pos() = { -170, 15 };
	slots["Glove"]->SetPixelShader(L"Slot.hlsl");
	//slots["Glove"]->SetParent(this);

	slots["Belt"] = new Quad(Vector2(85, 45));
	slots["Belt"]->SetTexture(L"Textures/UI/Inventory/BeltSlot.png");
	slots["Belt"]->Pos() = { 5, 40 };
	slots["Belt"]->SetPixelShader(L"Slot.hlsl");
	//slots["Belt"]->SetParent(this);


	slots["Boots"] = new Quad(Vector2(85, 85));
	slots["Boots"]->SetTexture(L"Textures/UI/Inventory/BootsSlot.png");
	slots["Boots"]->Pos() = { 175, 15 };
	slots["Boots"]->SetPixelShader(L"Slot.hlsl");
	//slots["Boots"]->SetParent(this);


}

void Inventory::CreateInventorySlot()
{
	inventorySlots.resize(INVENTORY_SLOT_SIZE.x * INVENTORY_SLOT_SIZE.y);

	Vector2 slotSize = { 43.8, 43.8 };
	Vector2 startPos = { Pos().x - 192, Pos().y - 78};


	for (int y = 0; y < INVENTORY_SLOT_SIZE.y; y++)
	{
		for (int x = 0; x < INVENTORY_SLOT_SIZE.x; x++)
		{
			int idx = y * INVENTORY_SLOT_SIZE.x + x;
			float xPos = startPos.x + slotSize.x * x;
			float yPos = startPos.y + -slotSize.y * y;
			inventorySlots[idx] = new InventorySlot({ xPos, yPos }, slotSize);
		}
	}
}

void Inventory::CreateItems()
{
	items["Helm"] = new Item(L"Textures/UI/items/helm.png", Vector2(2,2));
	items["Helm"]->SetDescription(L"Textures/UI/items/helm_info.png");
	items["Helm"]->SetInventory(this);
	items["Helm"]->SetItemType(Item::ItemType::HEAD);

	items["Body"] = new Item(L"Textures/UI/items/light_armor.png", Vector2(2, 3));
	items["Body"]->SetDescription(L"Textures/UI/items/light_armor_info.png");
	items["Body"]->SetInventory(this);
	items["Body"]->SetItemType(Item::ItemType::BODY);

	items["Wand"] = new Item(L"Textures/UI/items/wand.png", Vector2(1, 2));
	items["Wand"]->SetDescription(L"Textures/UI/items/wand_info.png");
	items["Wand"]->SetInventory(this);
	items["Wand"]->SetItemType(Item::ItemType::WEAPON);

	items["Glove"] = new Item(L"Textures/UI/items/leather_glove.png", Vector2(2, 2));
	items["Glove"]->SetDescription(L"Textures/UI/items/leather_glove_info.png");
	items["Glove"]->SetInventory(this);
	items["Glove"]->SetItemType(Item::ItemType::GLOVE);

	items["Belt"] = new Item(L"Textures/UI/items/belt.png", Vector2(2, 1));
	items["Belt"]->SetDescription(L"Textures/UI/items/belt_info.png");
	items["Belt"]->SetInventory(this);
	items["Belt"]->SetItemType(Item::ItemType::BELT);

	items["Boots"] = new Item(L"Textures/UI/items/boots.png", Vector2(2, 2));
	items["Boots"]->SetDescription(L"Textures/UI/items/boots_info.png");
	items["Boots"]->SetInventory(this);
	items["Boots"]->SetItemType(Item::ItemType::BOOTS);

	items["hpPotion"] = new Item(L"Textures/UI/items/hpPotion.png", Vector2(1, 1));
	items["hpPotion"]->SetDescription(L"Textures/UI/items/hpPotion_info.png");
	items["hpPotion"]->SetInventory(this);
	items["hpPotion"]->SetItemType(Item::ItemType::ETC);

	items["mpPotion"] = new Item(L"Textures/UI/items/mpPotion.png", Vector2(1, 1));
	items["mpPotion"]->SetDescription(L"Textures/UI/items/mpPotion_info.png");
	items["mpPotion"]->SetInventory(this);
	items["mpPotion"]->SetItemType(Item::ItemType::ETC);

	GetItem(items["Helm"]);
	GetItem(items["Body"]);
	GetItem(items["Wand"]);
	GetItem(items["Glove"]);
	GetItem(items["Belt"]);
	GetItem(items["Boots"]);
	GetItem(items["hpPotion"]);
	GetItem(items["mpPotion"]);
}
