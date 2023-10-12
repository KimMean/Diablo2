#pragma once

class Map
{
private :
	const Vector2 MAP_SIZE = { 101, 101 };
	const Vector2 TILE_SIZE = { 120, 60 };

	struct InstanceData
	{
		Matrix transform;
	};

public:
	Map();
	~Map();

	void Update();
	void Render();

	void GetNodes(vector<Node*>& nodes);
	UINT GetWidth() { return MAP_SIZE.x; }

private :
	void CreateTileMap();

	Vector2 MapLeftBottom();
	Vector2 MapRightTop();


private:
	vector<Tile*> bgTiles;
	vector<Tile*> objTiles;

	Quad* instanceQuad;
	Quad* instanceObjQuad;

	vector<InstanceData> instances;
	VertexBuffer* instanceBuffer;
};