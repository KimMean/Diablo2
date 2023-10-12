#include "Framework.h"

GameObject::GameObject(wstring shaderFile)
{
    vertexShader = Shader::AddVS(L"Vertex" + shaderFile);
    pixelShader = Shader::AddPS(L"Pixel" + shaderFile);

    worldBuffer = new MatrixBuffer();
}

GameObject::~GameObject()
{ 
    delete worldBuffer;
}

void GameObject::SetRender()
{   
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);    

    vertexShader->Set();
    pixelShader->Set();    
}

void GameObject::SetPixelShader(wstring shaderFile)
{
    pixelShader = Shader::AddPS(L"Pixel" + shaderFile);
}

void GameObject::SetVertexShader(wstring shaderFile)
{
    vertexShader = Shader::AddVS(L"Vertex" + shaderFile);
}

int GameObject::CompareObject(GameObject* obj1, GameObject* obj2)
{
    float obj1Bottom = obj1->GlobalPos().y - obj1->size.y * 0.5f;
    float obj2Bottom = obj2->GlobalPos().y - obj2->size.y * 0.5f;

    return obj1Bottom > obj2Bottom;
}
