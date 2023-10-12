//PixelImageFont
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

cbuffer ValueBuffer : register(b1)
{
	int value;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float2 uv = input.uv;
	uv.x += 0.1f * value;
	
	float4 tex = map.Sample(samp, uv);
	
	return tex * color;
}