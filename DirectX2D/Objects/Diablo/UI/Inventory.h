#pragma once

class Inventory : public Panel
{
private :
	Vector2 INVENTORY_SLOT_SIZE = { 10, 4 };
	Float4 COLOR_TRANS = { 1, 1, 1, 0 };
	Float4 COLOR_WHITE = { 1, 1, 1, 1 };
	Float4 COLOR_RED = { 1, 0, 0, 0.8f };
	Float4 COLOR_BLUE = { 0, 0, 1, 0.8f };

public:
	Inventory();
	~Inventory();

	void Update();
	void Render();

	void Hide();
	Collider* GetCollider() { return collider; }

	void DragAndDrop();
	bool IsMountable(Item* item, int slotIndex);
	void SetTargetItem(Item* item);
	bool GetItem(Item* item);
	bool IsDrop(Item* item);

private :
	void CreateSlot();
	void CreateInventorySlot();
	void CreateItems();

private:
	RectCollider* collider;

	Button* cancelBtn;

	unordered_map<string, Quad*> slots;
	unordered_map<string, Item*> items;

	Item* target = nullptr;
	vector<InventorySlot*> inventorySlots;
	
	//Quad* head;

};