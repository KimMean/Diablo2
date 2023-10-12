#pragma once

class GameObject : public Transform
{
public:
    GameObject(wstring shaderFile = L"UV.hlsl");
    ~GameObject();

    virtual void Render() {};
    virtual void SetRender();

    void SetPixelShader(wstring shaderFile);
    void SetVertexShader(wstring shaderFile);

    static int CompareObject(GameObject* obj1, GameObject* obj2);

protected:
    VertexShader* vertexShader;
    PixelShader* pixelShader;    
    MatrixBuffer* worldBuffer;

    Vector2 size;
};