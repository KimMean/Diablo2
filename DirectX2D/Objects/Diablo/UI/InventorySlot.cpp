#include "Framework.h"

InventorySlot::InventorySlot(Vector2 pos, Vector2 slotSize)
	: Quad(slotSize)
{
	SetPixelShader(L"Slot.hlsl");
	Pos() = pos;
	collider = new RectCollider(slotSize);
	collider->SetParent(this);
	
	UpdateWorld();
	collider->UpdateWorld();
	colorBuffer->Get() = { 1, 1, 1, 0 };
}

InventorySlot::~InventorySlot()
{
	delete collider;
}

void InventorySlot::Render()
{
	Quad::Render();
	collider->Render();
}
