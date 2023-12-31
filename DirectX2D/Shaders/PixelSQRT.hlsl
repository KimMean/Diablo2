struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 tex = map.Sample(samp, input.uv);
    tex.x = sqrt(tex.x);
    tex.y = sqrt(tex.y);
    tex.z = sqrt(tex.z);
	//return tex * color;
    return tex;
}