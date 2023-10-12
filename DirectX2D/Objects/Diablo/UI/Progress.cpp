#include "Framework.h"

Progress::Progress(wstring frontImageFile, bool isVertical)
    : Quad(frontImageFile), isVertical(isVertical)
{
    SetPixelShader(L"ProgressBar.hlsl");

    valueBuffer = new FloatValueBuffer();
    valueBuffer->Get()[0] = fillAmount;
    boolValueBuffer = new BoolValueBuffer();
    boolValueBuffer->Get() = isVertical;
}

Progress::~Progress()
{
    //delete valueBuffer;
    if (backImage)
        delete backImage;
}

void Progress::Render()
{
    valueBuffer->SetPS(1);
    boolValueBuffer->SetPS(2);


    if (backImage)
        backImage->Render();
    Quad::Render();
}

void Progress::SetBackImage(wstring backImageFile)
{
    backImage = new Quad(backImageFile);
    backImage->SetParent(this);
    backImage->UpdateWorld();
}

void Progress::SetAmount(float value)
{
    fillAmount = value;
    valueBuffer->Get()[0] = fillAmount;
}
