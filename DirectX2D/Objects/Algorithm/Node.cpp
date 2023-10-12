#include "Framework.h"

Node::Node(Vector2 pos, int index)
    : pos(pos), index(index)
{
    collider = new CircleCollider(10);
    collider->Pos() = pos;
    collider->UpdateWorld();
}

Node::~Node()
{
    for (Edge* edge : edges)
        delete edge;

    delete collider;
}

void Node::Render()
{
    switch (state)
    {
    case Node::NONE:
        collider->GetColor() = { 0, 1, 1, 1 };
        break;
    case Node::OPEN:
        collider->GetColor() = { 0, 0, 1, 1 };
        break;
    case Node::CLOSED:
        collider->GetColor() = { 0, 0, 0, 1 };
        break;
    case Node::USING:
        collider->GetColor() = { 0, 1, 0, 1 };
        break;
    case Node::OBSTACLE:
        collider->GetColor() = { 1, 0, 0, 1 };
        break;    
    }

    collider->Render();

    for (Edge* edge : edges)
        edge->line->Render();
}

void Node::AddEdge(Node* node)
{
    Edge* edge = new Edge(node->pos, pos);
    edge->index = node->index;
    edge->cost = Distance(node->pos, pos);

    edges.push_back(edge);
}
