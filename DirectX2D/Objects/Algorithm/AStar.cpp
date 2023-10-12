#include "Framework.h"

AStar::AStar()
{
}

AStar::~AStar()
{
    for (Node* node : nodes)
        delete node;

    delete heap;
}

void AStar::Update()
{
    if (KEY_DOWN(VK_RBUTTON))
    {
        for (Node* node : nodes)
        {
            if(node->collider->IsPointCollision(CAM->ScreenToWorld(mousePos)))
            {
                node->SetState(Node::OBSTACLE);
            }
        }
    }
}

void AStar::Render()
{
    for (Node* node : nodes)
    {
        if (CAM->ContainFrustum(node->pos, { 50, 50 }))
        {
            node->Render();
        }
    }
    // Node Render
    //for (Node* node : nodes)
    //    node->Render();
}

void AStar::SetTileMap(Map* map)
{
    map->GetNodes(nodes);
    SetEdge(map->GetWidth());

    heap = new Heap();
}

int AStar::FindCloseNode(Vector2 pos)
{
    float minDist = FLT_MAX;

    int index = -1;

    for (UINT i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->state == Node::OBSTACLE)
            continue;

        float distance = Distance(pos, nodes[i]->pos);

        if (minDist > distance)
        {
            minDist = distance;
            index = i;
        }
    }

    return index;
}

int AStar::FindRandomPos(Vector2 pos, float range)
{
    vector<Node*> findNodes;

    for (Node* node : nodes)
    {
        float distance = Distance(pos, node->pos);

        if (distance < range)
        {
            findNodes.push_back(node);
        }
    }

    Node* findNode = findNodes[Random(0, findNodes.size())];

    return findNode->index;
}

Vector2 AStar::GetNodePos(Vector2 pos)
{
    int idx = FindCloseNode(pos);

    return nodes[idx]->pos;
}

Vector2 AStar::GetRandomNodePos()
{
    int rnd = Random(0, nodes.size());
    
    return nodes[rnd]->pos;
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector2>& path)
{
    Reset();
    path.clear();

    float G = 0;
    float H = GetDiagonalManhattanDistance(start, end);

    nodes[start]->f = G + H;
    nodes[start]->g = G;
    nodes[start]->h = H;
    nodes[start]->via = start;
    nodes[start]->state = Node::OPEN;

    heap->Insert(nodes[start]);

    while (nodes[end]->state != Node::CLOSED)
    {
        if(heap->Empty())
            return;

        int curIndex = GetMinNode();
        Extend(curIndex, end);
        nodes[curIndex]->state = Node::CLOSED;
    }

    int curIndex = end;

    while (curIndex != start)
    {
        nodes[curIndex]->state = Node::USING;
        path.push_back(nodes[curIndex]->pos);
        curIndex = nodes[curIndex]->via;
    }
}

void AStar::Reset()
{
    for (Node* node : nodes)
    {
        if (node->state != Node::OBSTACLE)
            node->state = Node::NONE;
    }

    //openNodes.clear();
    heap->Clear();
}

float AStar::GetManhattanDistance(int start, int end)
{
    Vector2 startPos = nodes[start]->pos;
    Vector2 endPos = nodes[end]->pos;

    Vector2 temp = endPos - startPos;

    return abs(temp.x) + abs(temp.y);
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
    Vector2 startPos = nodes[start]->pos;
    Vector2 endPos = nodes[end]->pos;

    Vector2 temp = endPos - startPos;

    float x = abs(temp.x);
    float y = abs(temp.y);

    float maxSize = max(x, y);
    float minSize = min(x, y);

    return (maxSize - minSize) + sqrt(minSize * minSize * 2);
}

void AStar::Extend(int center, int end)
{
    for (Node::Edge* edge : nodes[center]->edges)
    {
        int index = edge->index;

        if (nodes[index]->state == Node::CLOSED)
            continue;
        if (nodes[index]->state == Node::OBSTACLE)
            continue;

        float G = nodes[center]->g + edge->cost;
        float H = GetDiagonalManhattanDistance(index, end);
        float F = G + H;

        if (nodes[index]->state == Node::OPEN)
        {
            if (F < nodes[index]->f)
            {
                nodes[index]->g = G;
                nodes[index]->f = F;
                nodes[index]->via = center;
            }
        }
        else if(nodes[index]->state == Node:: NONE)
        {
            nodes[index]->g = G;
            nodes[index]->h = H;
            nodes[index]->f = F;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN;

            //openNodes.push_back(index);
            heap->Insert(nodes[index]);
        }
    }
}

int AStar::GetMinNode()
{
    /*
    int openIndex = 0;
    int nodeIndex = openNodes[openIndex];
    float minF = nodes[nodeIndex]->f;

    for (UINT i = 0; i < openNodes.size(); i++)
    {
        nodeIndex = openNodes[i];
        if (nodes[nodeIndex]->f < minF)
        {
            minF = nodes[nodeIndex]->f;
            openIndex = i;
        }
    }

    nodeIndex = openNodes[openIndex];

    openNodes.erase(openNodes.begin() + openIndex);    
    return nodeIndex;
    */

    return heap->DeleteRoot()->index;
}

void AStar::SetEdge(UINT width)
{
    for (UINT i = 0; i < nodes.size(); i++)
    {
        if (i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + 1]);
            nodes[i + 1]->AddEdge(nodes[i]);
        }    
        if (i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width]);
            nodes[i + width]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width - 1]);
            nodes[i + width - 1]->AddEdge(nodes[i]);
        }
        
        if (i < nodes.size() - width && i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + width + 1]);
            nodes[i + width + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width * 2)
        {
            nodes[i]->AddEdge(nodes[i + width * 2]);
            nodes[i + width * 2]->AddEdge(nodes[i]);
        }
        
        if (i < nodes.size() - width * 3)
        {
            nodes[i]->AddEdge(nodes[i + width * 3]);
            nodes[i + width * 3]->AddEdge(nodes[i]);
        }
        
        if ((i / width) % 2 == 0)
        {
            if (i < nodes.size() - width && i % width > 2)
            {
                nodes[i]->AddEdge(nodes[i + width - 2]);
                nodes[i + width - 2]->AddEdge(nodes[i]);
            }
            if (i < nodes.size() - width * 3 && i % width != 0)
            {
                nodes[i]->AddEdge(nodes[i + width * 3 - 1]);
                nodes[i + width * 3 - 1]->AddEdge(nodes[i]);
            }
        }
        else
        {
            if (i < nodes.size() - width - 2 && i % width < width - 3)
            {
                nodes[i]->AddEdge(nodes[i + width + 2]);
                nodes[i + width + 2]->AddEdge(nodes[i]);
            }
            if (i < nodes.size() - width * 3 - 1 && i % width != width - 1)
            {
                nodes[i]->AddEdge(nodes[i + width * 3 + 1]);
                nodes[i + width * 3 + 1]->AddEdge(nodes[i]);
            }
        }
    }
}
