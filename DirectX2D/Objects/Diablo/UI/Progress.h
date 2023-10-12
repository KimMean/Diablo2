#pragma once

class Progress : public Quad
{
public:
	Progress(wstring frontImageFile, bool isVertical = false);
	~Progress();

    void Render();

    Quad* GetBackImage() { return backImage; }
    void SetBackImage(wstring backImageFile);
    void SetAmount(float value);


private:
    FloatValueBuffer* valueBuffer;
    BoolValueBuffer* boolValueBuffer;
    Quad* backImage = nullptr;

    bool isVertical;
    float fillAmount = 1.0f;

};