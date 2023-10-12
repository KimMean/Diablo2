#pragma once

class Item : public Button
{
public :
	enum ItemType
	{
		ETC,
		HEAD,
		BODY,
		BELT,
		BOOTS,
		GLOVE,
		WEAPON,
		SUB_WEAPON
	};

public:
	Item(wstring texture, Vector2 SlotSize);
	~Item();

	void Update();
	void Render();

	void SetInventory(class Inventory* inven) { this->inven = inven; }
	void OnClick();
	void SetIsDrag(bool drag) { isDrag = drag; }
	ItemType GetItemType() { return type; }
	void SetItemType(ItemType type) { this->type = type; }
	Vector2 GetSlotSize() { return slotSize; }
	void SetDescription(wstring texture);
	void ShowDescription(bool isActive);

private:
	ItemType type = ETC;
	class Inventory* inven = nullptr;
	bool isDrag = false;

	RectCollider* collider;
	Quad* description;
	bool showDescription;

	Vector2 slotSize;
};