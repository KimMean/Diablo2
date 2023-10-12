#pragma once

class Node
{
public:
    friend class AStar;

    enum State
    {
        NONE, OPEN, CLOSED, USING, OBSTACLE
    };

    struct Edge
    {
        int index;
        float cost;
        LineCollider* line;

        Edge(Vector2 start, Vector2 end)
        {
            line = new LineCollider(start, end);
            line->GetColor() = { 1, 1, 0, 1};
        }
        ~Edge()
        {
            delete line;
        }
    };

public:
    Node(Vector2 pos, int index);
    ~Node();

    void Render();

    void AddEdge(Node* node);

    void SetState(State state) { this->state = state; }
    float GetCost() { return f; }

private:
    Vector2 pos;

    int index = 0;
    int via = -1;

    //Cost
    float f = 0, g = 0, h = 0;

    State state = NONE;

    vector<Edge*> edges;

    Collider* collider;
};