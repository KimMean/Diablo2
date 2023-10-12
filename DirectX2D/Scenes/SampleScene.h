#pragma once

class SampleScene : public Scene
{
public:
    SampleScene();
    ~SampleScene();

    // Scene을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
};