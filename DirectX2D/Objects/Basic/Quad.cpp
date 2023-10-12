#include "Framework.h"

Quad::Quad(Vector2 size)       
{
    this->size = size;
    endUV = { 1, 1 };
    SetTexture(L"Textures/DefaultTexture.png");
    CreateMesh();

    colorBuffer = new ColorBuffer();
}

Quad::Quad(wstring file, Vector2 startUV, Vector2 endUV)
    : startUV(startUV), endUV(endUV)
{
    texture = Texture::Add(file);
    size = (endUV - startUV) * texture->GetSize();
    CreateMesh();    

    colorBuffer = new ColorBuffer();
}

Quad::~Quad()
{    
    delete vertexBuffer;
    delete indexBuffer;
    delete colorBuffer;
}

void Quad::Render()
{
    SetRender();

    DC->DrawIndexed(indices.size(), 0, 0);
}

void Quad::SetRender()
{
    texture->PSSet();

    vertexBuffer->Set();
    indexBuffer->Set();

    colorBuffer->SetPS(0);

    GameObject::SetRender();
}

void Quad::SetResizeTexture(Vector2 size)
{
    this->size = size;

    vertices.clear();

    float left = -size.x * 0.5f;
    float right = +size.x * 0.5f;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    vertices.emplace_back(left, top, startUV.x, startUV.y);
    vertices.emplace_back(right, top, endUV.x, startUV.y);
    vertices.emplace_back(left, bottom, startUV.x, endUV.y);
    vertices.emplace_back(right, bottom, endUV.x, endUV.y);

    delete vertexBuffer;
    delete indexBuffer;

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

void Quad::SetTexture(wstring file)
{
    SetTexture(Texture::Add(file));    
}

void Quad::SetTexture(Texture* texture)
{
    this->texture = texture;
    //size = (endUV - startUV) * texture->GetSize();
    //UpdateVertices();
}

void Quad::CreateMesh()
{
    float left = -size.x * 0.5f;
    float right = +size.x * 0.5f;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    vertices.emplace_back(left, top, startUV.x, startUV.y);
    vertices.emplace_back(right, top, endUV.x, startUV.y);
    vertices.emplace_back(left, bottom, startUV.x, endUV.y);
    vertices.emplace_back(right, bottom, endUV.x, endUV.y);

    indices = { 0, 1, 2, 2, 1, 3 };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

void Quad::UpdateVertices()
{
    float left = -size.x * 0.5f;
    float right = +size.x * 0.5f;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    vertices[0] = Vertex(left, top, startUV.x, startUV.y);
    vertices[1] = Vertex(right, top, endUV.x, startUV.y);
    vertices[2] = Vertex(left, bottom, startUV.x, endUV.y);
    vertices[3] = Vertex(right, bottom, endUV.x, endUV.y);

    vertexBuffer->Update(vertices.data(), vertices.size());
}
