#pragma once

class SampleScene : public Scene
{
public:
    SampleScene();
    ~SampleScene();

    // Scene��(��) ���� ��ӵ�
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
};