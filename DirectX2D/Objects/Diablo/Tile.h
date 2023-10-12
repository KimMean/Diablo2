#pragma once

class Tile : public Quad
{
public :
	enum Type
	{
		BG, OBJ
	};

public:
	Tile(Vector2 size);
	~Tile();

	void Update();
	void Render();

private:
	Type type = BG;

	RectCollider* collider;

};