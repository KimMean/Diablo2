#pragma once

class InventorySlot : public Quad
{
public:
	InventorySlot(Vector2 pos, Vector2 slotSize);
	~InventorySlot();

	void Render();

	Collider* GetCollider() { return collider; }
	void SetIsEmpty(bool isEmpty) { this->isEmpty = isEmpty; }
	bool IsEmpty() { return isEmpty; }

private:
	bool isEmpty = true;

	RectCollider* collider;

	string itemName;

};