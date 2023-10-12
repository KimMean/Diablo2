#include "Framework.h"

Tile::Tile(Vector2 size)
	: Quad(size)
{
	float width = sqrt(pow(size.x * 0.5f, 2) + pow(size.y * 0.5f, 2));
	//collider = new RectCollider(size * 0.5f);
	//collider = new RectCollider(Vector2(width, width * 0.5f));
	collider = new RectCollider(size.x * 0.5f, size.y * 0.5f);
	collider->SetParent(this);
	collider->UpdateWorld();
	//collider->Rot().z = XM_PIDIV4;
	//UpdateWorld();
}

Tile::~Tile()
{
	delete collider;
}

void Tile::Update()
{
	UpdateWorld();
	collider->UpdateWorld();
}

void Tile::Render()
{
	Quad::Render();
	collider->Render();
}
