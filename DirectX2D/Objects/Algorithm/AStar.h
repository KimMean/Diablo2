#pragma once

class AStar : public Singleton<AStar>
{
private :
    friend class Singleton;

    AStar();
    ~AStar();

public :

    void Update();
    void Render();

    void SetTileMap(class Map* map);

    int FindCloseNode(Vector2 pos);
    int FindRandomPos(Vector2 pos, float range);
    Vector2 GetNodePos(Vector2 pos);
    Vector2 GetRandomNodePos();

    void GetPath(IN int start, IN int end, OUT vector<Vector2>& path);

private:
    void Reset();

    float GetManhattanDistance(int start, int end);
    float GetDiagonalManhattanDistance(int start, int end);

    void Extend(int center, int end);
    int GetMinNode();

    void SetEdge(UINT width);

private:
    vector<Node*> nodes;
    Heap* heap;
};