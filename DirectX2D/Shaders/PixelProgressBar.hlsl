struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

Texture2D frontMap : register(t0);
Texture2D backMap : register(t1);

SamplerState samp : register(s0);

cbuffer ValueBuffer : register(b1)
{
	float fillAmount;
}

cbuffer ValueBuffer : register(b2)
{
    bool isVertical;
}

float4 PS(PixelInput input) : SV_TARGET
{
    if (isVertical)
    {
        if (input.uv.y < 1.0f - fillAmount)
            return float4(0, 0, 0, 0);
    }
    else
    {
        if (input.uv.x > fillAmount)
            return float4(0, 0, 0, 0);
    }
        
    
	//return backMap.Sample(samp, input.uv);
    return frontMap.Sample(samp, input.uv);
}