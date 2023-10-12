#pragma once

class Panel : public Quad
{
public:
    Panel(wstring bgTextureFile);
    Panel(wstring bgTextureFile, Vector2 size);
    ~Panel();

    virtual void Update();
    virtual void Render();

    void Show();
    void Hide();

private:
    Vector2 offset;    
    bool isDrag = false;
};