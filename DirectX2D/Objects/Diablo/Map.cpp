#include "Framework.h"

Map::Map()
{
	CreateTileMap();
	CAM->SetLeftBottom(MapLeftBottom());
	CAM->SetRightTop(MapRightTop());

	instances.resize(MAP_SIZE.x * MAP_SIZE.y);
	instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), MAP_SIZE.x * MAP_SIZE.y);

	instanceQuad = new Quad(TILE_SIZE);
	instanceQuad->SetTexture(L"Textures/Tiles/01.png");
	instanceQuad->SetVertexShader(L"Instancing.hlsl");
	instanceQuad->SetPixelShader(L"Instancing.hlsl");

	instanceObjQuad = new Quad(TILE_SIZE);
	instanceObjQuad->SetTexture(L"Textures/TileObjects/obj10.png");
	instanceObjQuad->SetVertexShader(L"Instancing.hlsl");
	instanceObjQuad->SetPixelShader(L"Instancing.hlsl");
}

Map::~Map()
{
	for (Tile* tile : bgTiles)
	{
		delete tile;
	}
	for (Tile* tile : objTiles)
	{
		delete tile;
	}
	delete instanceQuad;
	delete instanceObjQuad;
}

void Map::Update()
{
	//for (Tile* tile : bgTiles)
	//{
	//	if (CAM->ContainFrustum(tile->GlobalPos(), tile->GetSize()))
	//	{
	//		tile->Update();
	//	}
	//}
}

void Map::Render()
{
	int cnt = 0;
	instances.clear();
	for (Tile* tile : bgTiles)
	{
		if (CAM->ContainFrustum(tile->GlobalPos(), tile->GetSize()))
		{
			InstanceData insData;
			insData.transform = XMMatrixTranspose(tile->GetWorld());
			instances.push_back(insData);
			//tile->Render();
		}
	}
	instanceBuffer->Update(instances.data(), sizeof(InstanceData));
	instanceBuffer->Set(1);
	
	instanceQuad->SetRender();

	DC->DrawIndexedInstanced(6, instances.size(), 0, 0, 0);

	//instances.clear();
	for (Tile* tile : objTiles)
	{
		if (CAM->ContainFrustum(tile->GlobalPos(), tile->GetSize()))
		{
			tile->Render();
			//InstanceData insData;
			//insData.transform = XMMatrixTranspose(tile->GetWorld());
			//instances.push_back(insData);
		}
	}
	// юс╫ц
	//for (Tile* tile : bgTiles)
	//{
	//	if (CAM->ContainFrustum(tile->GlobalPos(), tile->GetSize()))
	//	{
	//		tile->Render();
	//	}
	//}
	//instanceBuffer->Update(instances.data(), sizeof(InstanceData));
	//instanceBuffer->Set(1);
	//instanceObjQuad->SetRender();
	//
	//DC->DrawIndexedInstanced(6, objTiles.size(), 0, 0, 0);
}

void Map::GetNodes(vector<Node*>& nodes)
{
	for (Quad* tile : bgTiles)
	{
		Vector2 tilePos = tile->GlobalPos();
		Node* node = new Node(tilePos, nodes.size());

		for (Tile* obj : objTiles)
		{
			Vector2 objPos = obj->GlobalPos();
		
			if (objPos == tilePos)
			{
				node->SetState(Node::OBSTACLE);
			}
		}

		nodes.push_back(node);
	}
}

void Map::CreateTileMap()
{
	bgTiles.reserve(MAP_SIZE.x * MAP_SIZE.y);
	//for (Tile*& tile : bgTiles)
	for(int y = 0; y < MAP_SIZE.y; y++)
	{
		for (int x = 0; x < MAP_SIZE.x; x++)
		{
			Tile* tile = new Tile(Vector2(TILE_SIZE));
			int rnd = Random(1, 20);
			tile->SetTexture(L"Textures/Tiles/01.png");
			//if(rnd < 10)
			//	tile->SetTexture(L"Textures/Tiles/0" + to_wstring(rnd) + L".png");
			//else
			//	tile->SetTexture(L"Textures/Tiles/" + to_wstring(rnd) + L".png");
			tile->Pos() = Vector2(TILE_SIZE.x * x, TILE_SIZE.y * 0.5f * y);
			//tile->Pos() = Vector2(CENTER_X, CENTER_Y);
			if (y % 2 > 0)
				tile->Pos().x += TILE_SIZE.x * 0.5f;

			tile->Update();

			//InstanceData insData;
			//insData.transform = XMMatrixTranspose(tile->GetWorld());
			//instances[y * MAP_SIZE.y + x].transform = XMMatrixTranspose(tile->GetWorld());

			bgTiles.push_back(tile);
		}
	}
	//instanceBuffer->Update(instances.data(), sizeof(InstanceData));
	objTiles.reserve(MAP_SIZE.x* MAP_SIZE.y);
	for (int y = 0; y < MAP_SIZE.y; y++)
	{
		for (int x = 0; x < MAP_SIZE.x; x++)
		{
			wstring textureFile;
			
			int rnd = Random(0, 100);
			if (rnd > 20) continue;
			
			rnd %= 3;
			if(rnd == 0)
				textureFile = L"Textures/TileObjects/obj10.png";
			else if (rnd == 1)
				textureFile = L"Textures/TileObjects/obj14.png";
			else
				textureFile = L"Textures/TileObjects/obj15.png";

			Tile* tile = new Tile(Vector2(TILE_SIZE));
			tile->SetTexture(textureFile);
			tile->Pos() = Vector2(TILE_SIZE.x * x, TILE_SIZE.y * 0.5f * y);
			//tile->SetPixelShader(L"SQRT.hlsl");
			//tile->Pos() = Vector2(CENTER_X, CENTER_Y);
			if (y % 2 > 0)
				tile->Pos().x += TILE_SIZE.x * 0.5f;

			//tile->UpdateWorld();
			tile->Update();
			objTiles.push_back(tile);
		}
	}
}

Vector2 Map::MapLeftBottom()
{
	return TILE_SIZE * 0.5f;
}

Vector2 Map::MapRightTop()
{
	return MAP_SIZE * TILE_SIZE - TILE_SIZE * 0.5f;
}
